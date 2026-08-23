#pragma once
#include <atomic>

namespace quanttrading
{
// 进程级退出请求：信号处理器仅置位原子标志（信号上下文安全），
// 主线程轮询 IsRequested() 后按依赖序执行有序关停。
class ShutdownSignal
{
public:
    static void InstallHandlers();
    static void Request();
    static bool IsRequested();

private:
    inline static std::atomic<bool> s_Requested{false};
};
}
