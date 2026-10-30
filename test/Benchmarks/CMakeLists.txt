# 可执行文件统一用 Bench 前缀，与 Test* 一样在 bin/<Config> 里排在一处；
# 每个基准独占一个同名源目录（add_application 会递归收集源目录下的全部 .cpp），
# 计时器是 Spark 的公开头 <Spark/TemplateLib/Benchmark/BenchmarkRunner.h>，与兄弟仓的 CSV 口径一致
add_application(BenchBarAggregator ${CMAKE_CURRENT_SOURCE_DIR}/BenchBarAggregator ${CMAKE_CURRENT_SOURCE_DIR}/BenchBarAggregator)
add_application(BenchOrderMatch   ${CMAKE_CURRENT_SOURCE_DIR}/BenchOrderMatch ${CMAKE_CURRENT_SOURCE_DIR}/BenchOrderMatch)
add_application(BenchPackageCodec ${CMAKE_CURRENT_SOURCE_DIR}/BenchPackageCodec ${CMAKE_CURRENT_SOURCE_DIR}/BenchPackageCodec)

target_link_libraries(BenchBarAggregator PRIVATE BarStatic Spark::Core)
target_link_libraries(BenchOrderMatch PRIVATE OrderMatchStatic MdbStatic PackagesStatic Spark::Core)
target_link_libraries(BenchPackageCodec PRIVATE PackagesStatic Spark::Network Spark::Core)

foreach(benchmarkTarget BenchBarAggregator BenchOrderMatch BenchPackageCodec)
    copy_dll_file(${benchmarkTarget})
endforeach()
