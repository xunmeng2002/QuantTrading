# Python 策略绑定模块：产出 quanttrading.pyd（import 名 quanttrading），落 bin/<CONFIG> 与
# BackTestd.dll、BackTest.json 同目录，Python 策略以 bin/<CONFIG> 为工作目录运行
pybind11_add_module(quanttrading QuantTradingBindings.cpp FieldsBindings.cpp)
target_link_libraries(quanttrading PRIVATE StrategyStatic BackTestApiMiddleStatic)
set_target_properties(quanttrading PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>
	# 去掉全局 CMAKE_DEBUG_POSTFIX 的 "d" 后缀：模块名必须始终是 quanttrading
	DEBUG_POSTFIX "")
copy_dll_file(quanttrading)
