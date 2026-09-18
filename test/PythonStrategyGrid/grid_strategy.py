"""成对网格策略 Python 移植（对应 test/TestStrategyGrid/GridStrategy.cpp，经 QuantTrading.pyd 驱动回测引擎）。

运行方式（脚本与配置由构建拷贝至 bin/Release，引擎从 CWD 读 BackTest.json 与 TestStrategyGrid.json）：
    cd bin/Release && python grid_strategy.py
"""

import json
import os
import sys
from dataclasses import dataclass
from enum import IntEnum

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(REPO_ROOT, "bin", "Release"))

import QuantTrading as qt


class GridSlotState(IntEnum):
    Empty = 0
    OpenPending = 1
    OpenFilled = 2
    ClosePending = 3
    Closed = 4


class GridSlot:
    def __init__(self, direction):
        self.direction = direction
        self.state = GridSlotState.Empty
        self.open_price = 0.0
        self.open_fill_price = 0.0
        self.close_price = 0.0
        self.open_client_order_id = 0
        self.close_client_order_id = 0
        self.open_filled_volume = 0
        self.close_filled_volume = 0


@dataclass
class GridParams:
    grid_step: float
    grid_count: int
    volume_per_grid: int
    exchange_id: str
    instrument_id: str
    bar_preces: str = ""   # 策略期望 bar 周期（"5m" 格式，同 BackTest.json BarPreces）；空=on_bar 纯透传


class GridStrategy(qt.StrategyBase):
    """格位状态机 Empty → OpenPending → OpenFilled → ClosePending → Closed，日级重锚。

    [0, GridCount) 为买开格，[GridCount, 2×GridCount) 为卖开格；平仓价取开仓成交价 ∓ 步长，与锚点无关。
    引擎日切结算统一撤销全部未成交挂单：零成交开仓格复位 Empty 等次日重锚重挂；部分成交开仓格
    与被撤平仓格按已成交/剩余量即时补平仓单，新平仓单经引擎队列在次一交易日撮合。
    """

    def __init__(self, backtest_api, account_id, params):
        super().__init__(backtest_api=backtest_api, account_id=account_id)
        self.params = params
        if params.bar_preces:
            self.declare_bar_period(params.bar_preces)
        self.slots = [GridSlot(qt.DirectionType.Buy) for _ in range(params.grid_count)] + \
            [GridSlot(qt.DirectionType.Sell) for _ in range(params.grid_count)]
        self.awaiting_anchor = True
        self.closed_pair_count = 0
        self.realized_profit = 0.0
        self.total_commission = 0.0

    def on_start(self):
        self.subscribe_tick(self.params.exchange_id, self.params.instrument_id)

    def on_tick(self, market_data):
        if not self.awaiting_anchor:
            return
        anchor_price = market_data.last_price
        if anchor_price <= 0 or anchor_price == sys.float_info.max:
            return
        self.awaiting_anchor = False
        print("Anchor price: %f" % anchor_price)
        self.place_ladder(anchor_price)

    def place_ladder(self, anchor_price):
        for level in range(self.params.grid_count):
            buy_slot = self.slots[level]
            if buy_slot.state == GridSlotState.Empty:
                buy_slot.open_price = anchor_price - self.params.grid_step * (level + 1)
                self.place_open_order(buy_slot)
            sell_slot = self.slots[self.params.grid_count + level]
            if sell_slot.state == GridSlotState.Empty:
                sell_slot.open_price = anchor_price + self.params.grid_step * (level + 1)
                self.place_open_order(sell_slot)

    def place_open_order(self, slot):
        slot.open_filled_volume = 0
        if slot.direction == qt.DirectionType.Buy:
            slot.open_client_order_id = self.buy_open(
                self.params.exchange_id, self.params.instrument_id, slot.open_price, self.params.volume_per_grid)
        else:
            slot.open_client_order_id = self.sell_open(
                self.params.exchange_id, self.params.instrument_id, slot.open_price, self.params.volume_per_grid)
        slot.state = GridSlotState.OpenPending

    def place_close_order(self, slot, volume):
        if slot.direction == qt.DirectionType.Buy:
            slot.close_client_order_id = self.sell_close(
                self.params.exchange_id, self.params.instrument_id, slot.close_price, volume)
        else:
            slot.close_client_order_id = self.buy_close(
                self.params.exchange_id, self.params.instrument_id, slot.close_price, volume)
        slot.state = GridSlotState.ClosePending

    def on_trade(self, trade, client_order_id):
        if client_order_id == 0:
            return
        slot = self.find_slot_by_open_order(client_order_id)
        if slot is not None:
            self.handle_open_trade(trade, slot)
            return
        slot = self.find_slot_by_close_order(client_order_id)
        if slot is not None:
            self.handle_close_trade(trade, slot)

    def on_order(self, order):
        if order.order_status != qt.OrderStatusType.Canceled and \
                order.order_status != qt.OrderStatusType.PartTradedCanceled:
            return
        slot = self.find_slot_by_open_order(order.client_order_id)
        if slot is not None:
            self.handle_open_order_canceled(slot)
            return
        slot = self.find_slot_by_close_order(order.client_order_id)
        if slot is not None:
            self.handle_close_order_canceled(slot)

    def on_insert_order_rsp(self, req_insert_order, rsp_info):
        if rsp_info.error_id == 0:
            return
        slot = self.find_slot_by_open_order(req_insert_order.client_order_id)
        if slot is not None:
            if slot.state == GridSlotState.OpenPending:
                self.reset_slot_to_empty(slot)
                print("Open order rejected, slot reset to Empty, Price:%f" % slot.open_price)
            return
        slot = self.find_slot_by_close_order(req_insert_order.client_order_id)
        if slot is not None:
            print("Close order rejected, position remains, ClosePrice:%f" % slot.close_price)

    def handle_open_trade(self, trade, slot):
        if slot.state != GridSlotState.OpenPending:
            return
        slot.open_fill_price = trade.price
        slot.open_filled_volume += trade.volume
        if slot.open_filled_volume < self.params.volume_per_grid:
            return
        self.update_close_price(slot)
        self.place_close_order(slot, slot.open_filled_volume)

    def handle_close_trade(self, trade, slot):
        if slot.state != GridSlotState.ClosePending:
            return
        slot.close_filled_volume += trade.volume
        if slot.close_filled_volume < slot.open_filled_volume:
            return
        if slot.direction == qt.DirectionType.Buy:
            profit_per_unit = trade.price - slot.open_fill_price
        else:
            profit_per_unit = slot.open_fill_price - trade.price
        pair_profit = profit_per_unit * trade.volume * trade.volume_multiple - trade.commission
        self.realized_profit += pair_profit
        self.total_commission += trade.commission
        self.closed_pair_count += 1
        slot.state = GridSlotState.Closed
        print("Pair closed, open:%f close:%f profit:%f" % (slot.open_fill_price, trade.price, pair_profit))

    def update_close_price(self, slot):
        if slot.direction == qt.DirectionType.Buy:
            slot.close_price = slot.open_fill_price + self.params.grid_step
        else:
            slot.close_price = slot.open_fill_price - self.params.grid_step

    def reset_slot_to_empty(self, slot):
        # 清净周期态字段：格位跨周期复用，残留 CloseFilledVolume 会使平仓剩余量算成 0，格位困死
        slot.state = GridSlotState.Empty
        slot.open_client_order_id = 0
        slot.close_client_order_id = 0
        slot.open_filled_volume = 0
        slot.close_filled_volume = 0

    def handle_open_order_canceled(self, slot):
        if slot.state != GridSlotState.OpenPending:
            return
        if slot.open_filled_volume == 0:
            self.reset_slot_to_empty(slot)
            print("Open order canceled without fill, slot reset to Empty, Price:%f" % slot.open_price)
            return
        self.update_close_price(slot)
        self.place_close_order(slot, slot.open_filled_volume)
        print("Partially filled open order canceled by day-end settlement, close volume:%d" % slot.open_filled_volume)

    def handle_close_order_canceled(self, slot):
        if slot.state != GridSlotState.ClosePending:
            return
        remaining_volume = slot.open_filled_volume - slot.close_filled_volume
        if remaining_volume <= 0:
            print("Close order canceled with zero remaining volume, ClosePrice:%f" % slot.close_price)
            return
        self.place_close_order(slot, remaining_volume)
        print("Close order canceled by day-end settlement, re-place close volume:%d" % remaining_volume)

    def on_session_begin(self, session_begin):
        # 引擎已在结算时统一撤单（撤单回报先于 SessionEnd）：OpenPending 格位已复位/转换，
        # 此处仅需复位 Closed 格等待重锚
        for slot in self.slots:
            if slot.state == GridSlotState.Closed:
                self.reset_slot_to_empty(slot)
        self.awaiting_anchor = True

    def on_session_end(self, session_end):
        close_pending_count = 0
        for slot in self.slots:
            if slot.state == GridSlotState.ClosePending:
                close_pending_count += 1
        print("Session end: %d slots closing next day after day-end cancel sweeps" % close_pending_count)

    def on_end(self):
        print("Grid strategy end: closedPairs:%d realizedProfit:%f totalCommission:%f longPosition:%d shortPosition:%d" % (
            self.closed_pair_count, self.realized_profit, self.total_commission,
            self.get_long_position(self.params.instrument_id), self.get_short_position(self.params.instrument_id)))

    def find_slot_by_open_order(self, client_order_id):
        for slot in self.slots:
            if slot.open_client_order_id == client_order_id:
                return slot
        return None

    def find_slot_by_close_order(self, client_order_id):
        for slot in self.slots:
            if slot.close_client_order_id == client_order_id:
                return slot
        return None


RESULT_FILE_NAME = "result.json"

# 退出码契约（与 src/BackTest/RunResult.h 同源）：
# 0 成功 / 1 宿主启动失败 / 2 结果文件缺失或不可解析 / 3 引擎报告失败
EXIT_CODE_HOST_INIT_FAILED = 1
EXIT_CODE_RESULT_FILE_UNREADABLE = 2
EXIT_CODE_ENGINE_FAILED = 3


def read_exit_code(result_file_path):
    """按结果契约把 result.json 映射成退出码；文件缺失或坏掉一律算「本轮没走完收尾」。"""
    try:
        with open(result_file_path, encoding="utf-8") as result_file:
            run_result = json.load(result_file)
    except (OSError, ValueError):
        return EXIT_CODE_RESULT_FILE_UNREADABLE
    return 0 if run_result.get("Success", False) else EXIT_CODE_ENGINE_FAILED


def main():
    with open("TestStrategyGrid.json", encoding="utf-8") as config_file:
        config = json.load(config_file)
    qt.init_logger(sys.argv[0], config["LogLevel"])
    # 启动前先删陈旧结果，让「文件不存在」等价于「本轮没走完收尾」
    try:
        os.remove(RESULT_FILE_NAME)
    except FileNotFoundError:
        pass
    api = qt.create_backtest_api()
    params = GridParams(
        grid_step=config["GridStep"],
        grid_count=config["GridCount"],
        volume_per_grid=config["VolumePerGrid"],
        exchange_id=config["ExchangeId"],
        instrument_id=config["InstrumentId"],
        bar_preces=config.get("BarPreces", ""))
    strategy = GridStrategy(api, config["AccountId"], params)
    if not strategy.start():
        qt.shutdown_logger()
        return EXIT_CODE_HOST_INIT_FAILED
    strategy.wait_for_end()
    qt.shutdown_logger()
    return read_exit_code(RESULT_FILE_NAME)


if __name__ == "__main__":
    sys.exit(main())
