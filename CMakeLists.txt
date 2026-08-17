cmake_minimum_required(VERSION 3.20)
include(submodules/CMakeCommon/CMakeCommon.cmake)
restore_vcpkg_root()
reuse_git_proxy_for_vcpkg()
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
message(STATUS "ENV{VCPKG_ROOT} = $ENV{VCPKG_ROOT}")
message(STATUS "ENV{VCPKG_DOWNLOADS} = $ENV{VCPKG_DOWNLOADS}")
message(STATUS "ENV{VCPKG_DEFAULT_BINARY_CACHE} = $ENV{VCPKG_DEFAULT_BINARY_CACHE}")
message(STATUS "CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
SET(PROJECT_NAME "QuantTrading")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(submodules/CMakeCommon/CMakeCommon.cmake)

# 用 project() 的 VERSION 生成版本头文件到构建目录。
# 各模块宏已把 ${CMAKE_CURRENT_BINARY_DIR} 挂入 PUBLIC include 路径，故所有 target 均可访问。
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/QuantTrading/Version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/QuantTrading/Version.h
    @ONLY
)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_VERBOSE_MAKEFILE ON)
add_definitions(-DUNICODE -D_UNICODE)


IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /bigobj /utf-8")
    add_definitions(-DWINDOWS -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
	add_compile_options(
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/Zi>
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:RelWithDebInfo>:/O2>
        $<$<CONFIG:RelWithDebInfo>:/Zi>
        $<$<CONFIG:MinSizeRel>:/O1>)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
	add_definitions("-DLINUX")
    add_compile_options(
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-ggdb>
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:RelWithDebInfo>:-O2>
        $<$<CONFIG:RelWithDebInfo>:-g>
        $<$<CONFIG:MinSizeRel>:-Os>)
    add_compile_definitions(
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:RelWithDebInfo>:NDEBUG>
        $<$<CONFIG:MinSizeRel>:NDEBUG>)
ENDIF()
message("CMAKE_BUILD_TYPE:" ${CMAKE_BUILD_TYPE})
message("CMAKE_SYSTEM_NAME:" ${CMAKE_SYSTEM_NAME})
message("CMAKE_CL_64:" ${CMAKE_CL_64})
message("CMAKE_CXX_FLAGS:" ${CMAKE_CXX_FLAGS})
message("CMAKE_CXX_FLAGS_RELEASE:" ${CMAKE_CXX_FLAGS_RELEASE})
message("CMAKE_CXX_FLAGS_DEBUG:" ${CMAKE_CXX_FLAGS_DEBUG})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/$<CONFIG>)

set(VCPKG_APPLOCAL_DEPS ON)

message(STATUS "VCPKG_TARGET_TRIPLET = ${VCPKG_TARGET_TRIPLET}")
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")

if(WIN32)
    find_package(Spark REQUIRED PATHS "../Libs/Spark/x64-windows")
    find_package(DBAdapters CONFIG REQUIRED PATHS "../Libs/DBAdapters/x64-windows")
    find_package(duckdb CONFIG REQUIRED PATHS "../Libs/duckdb/x64-windows")
    find_package(CTP CONFIG REQUIRED PATHS "../Libs/Ctp/x64-windows")
else()
    find_package(Spark REQUIRED PATHS "../Libs/Spark/x64-linux")
    find_package(DBAdapters CONFIG REQUIRED PATHS "../Libs/DBAdapters/x64-linux")
    find_package(duckdb CONFIG REQUIRED PATHS "../Libs/duckdb/x64-linux")
    find_package(CTP CONFIG REQUIRED PATHS "../Libs/Ctp/x64-linux")
endif()

add_library(QuantTradingInterface INTERFACE)
target_include_directories(QuantTradingInterface INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

add_static_md_module(QuantTradingCommon ${CMAKE_CURRENT_SOURCE_DIR}/src/QuantTradingCommon ${CMAKE_CURRENT_SOURCE_DIR}/src/QuantTradingCommon)
target_link_libraries(QuantTradingCommonStatic PUBLIC QuantTradingInterface Spark::Core)
target_link_libraries(QuantTradingCommonStatic PRIVATE Spark::Serialization)

add_static_md_module(Mdb ${CMAKE_CURRENT_SOURCE_DIR}/src/Mdb ${CMAKE_CURRENT_SOURCE_DIR}/src/Mdb)
target_link_libraries(MdbStatic PUBLIC QuantTradingInterface Spark::Core DBAdapters::DBInterface)
target_link_libraries(MdbStatic PRIVATE Spark::TemplateLib)

add_static_md_module(Packages ${CMAKE_CURRENT_SOURCE_DIR}/src/Packages ${CMAKE_CURRENT_SOURCE_DIR}/src/Packages)
target_link_libraries(PackagesStatic PUBLIC QuantTradingInterface Spark::Network)
target_link_libraries(PackagesStatic PRIVATE Spark::TemplateLib Spark::Core)


add_static_md_module(Bar ${CMAKE_CURRENT_SOURCE_DIR}/src/Bar ${CMAKE_CURRENT_SOURCE_DIR}/src/Bar)
target_link_libraries(BarStatic PUBLIC QuantTradingInterface QuantTradingCommonStatic PackagesStatic)
target_link_libraries(BarStatic PRIVATE Spark::Core)

add_static_md_module(OrderMatch ${CMAKE_CURRENT_SOURCE_DIR}/src/OrderMatch ${CMAKE_CURRENT_SOURCE_DIR}/src/OrderMatch)
target_link_libraries(OrderMatchStatic PUBLIC QuantTradingInterface MdbStatic PackagesStatic)
target_link_libraries(OrderMatchStatic PRIVATE QuantTradingCommonStatic Spark::Core)


add_library(CtpHeaders INTERFACE)
get_target_property(CTP_INCLUDE_DIR CTP::traderapi INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(CtpHeaders INTERFACE ${CTP_INCLUDE_DIR})
target_compile_options(CtpHeaders INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/wd4828>)

add_static_md_module(CtpStructLogFunc ${CMAKE_CURRENT_SOURCE_DIR}/src/Ctp/StructLogFunc ${CMAKE_CURRENT_SOURCE_DIR}/src/Ctp/StructLogFunc)
target_link_libraries(CtpStructLogFuncStatic PUBLIC CtpHeaders)
target_link_libraries(CtpStructLogFuncStatic PRIVATE Spark::Core)

add_static_md_module(CtpMdApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/src/Ctp/MdApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/src/Ctp/MdApiMiddle)
target_link_libraries(CtpMdApiMiddleStatic PUBLIC CtpHeaders CTP::mdapi)
target_link_libraries(CtpMdApiMiddleStatic PRIVATE Spark::Core CtpStructLogFuncStatic)

add_static_md_module(CtpTraderApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/src/Ctp/TraderApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/src/Ctp/TraderApiMiddle)
target_link_libraries(CtpTraderApiMiddleStatic PUBLIC CtpHeaders CTP::traderapi)
target_link_libraries(CtpTraderApiMiddleStatic PRIVATE Spark::Core CtpStructLogFuncStatic)


add_application(MdOffer  ${CMAKE_CURRENT_SOURCE_DIR}/src/MdOffer ${CMAKE_CURRENT_SOURCE_DIR}/src/MdOffer)
target_link_libraries(MdOffer PRIVATE QuantTradingInterface QuantTradingCommonStatic MdbStatic PackagesStatic BarStatic CtpMdApiMiddleStatic
    Spark::TemplateLib Spark::Core Spark::Network Spark::Serialization
    DBAdapters::DBInterface DBAdapters::AsyncDBWriter DBAdapters::SqliteWrapper DBAdapters::DuckdbWrapper DBAdapters::MysqlWrapper DBAdapters::MariadbWrapper)
copy_dll_file(MdOffer)
copy_config_file(MdOffer ${CMAKE_CURRENT_SOURCE_DIR}/Configs/MdOffer.json)
copy_config_file(MdOffer ${CMAKE_CURRENT_SOURCE_DIR}/Configs/CtpAccountInfo.json)
copy_config_file(MdOffer ${CMAKE_CURRENT_SOURCE_DIR}/Configs/Sessions.json)
copy_config_file(MdOffer ${CMAKE_CURRENT_SOURCE_DIR}/Configs/ServerConfig.json)


add_application(SimExchange  ${CMAKE_CURRENT_SOURCE_DIR}/src/SimExchange ${CMAKE_CURRENT_SOURCE_DIR}/src/SimExchange)
target_link_libraries(SimExchange PRIVATE QuantTradingInterface QuantTradingCommonStatic MdbStatic PackagesStatic OrderMatchStatic
    Spark::TemplateLib Spark::Core Spark::Network Spark::Serialization
    DBAdapters::DBInterface DBAdapters::AsyncDBWriter DBAdapters::SqliteWrapper DBAdapters::DuckdbWrapper DBAdapters::MysqlWrapper DBAdapters::MariadbWrapper)
copy_dll_file(SimExchange)
copy_config_file(SimExchange ${CMAKE_CURRENT_SOURCE_DIR}/Configs/SimExchange.json)


add_shared_module(BackTest  ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src/BackTest)
target_link_libraries(BackTest PRIVATE QuantTradingCommonStatic MdbStatic PackagesStatic OrderMatchStatic
    Spark::Core Spark::Serialization
    DBAdapters::DBInterface DBAdapters::AsyncDBWriter DBAdapters::SqliteWrapper DBAdapters::DuckdbWrapper DBAdapters::MysqlWrapper DBAdapters::MariadbWrapper)

add_application(SimExchangeInit  ${CMAKE_CURRENT_SOURCE_DIR}/src/SimExchangeInit ${CMAKE_CURRENT_SOURCE_DIR}/src/SimExchangeInit)
target_link_libraries(SimExchangeInit PRIVATE QuantTradingInterface QuantTradingCommonStatic MdbStatic CtpTraderApiMiddleStatic
    Spark::TemplateLib Spark::Core Spark::Network Spark::Serialization
    DBAdapters::DBInterface DBAdapters::AsyncDBWriter DBAdapters::SqliteWrapper DBAdapters::DuckdbWrapper DBAdapters::MysqlWrapper DBAdapters::MariadbWrapper)
copy_dll_file(SimExchangeInit)
copy_config_file(SimExchangeInit ${CMAKE_CURRENT_SOURCE_DIR}/Configs/SimExchangeInit.json)


add_application(BackTestInit  ${CMAKE_CURRENT_SOURCE_DIR}/src/BackTestInit ${CMAKE_CURRENT_SOURCE_DIR}/src/BackTestInit)
target_link_libraries(BackTestInit PRIVATE QuantTradingInterface QuantTradingCommonStatic MdbStatic
    Spark::TemplateLib Spark::Core Spark::Network Spark::Serialization
    DBAdapters::DBInterface DBAdapters::AsyncDBWriter DBAdapters::SqliteWrapper DBAdapters::DuckdbWrapper DBAdapters::MysqlWrapper DBAdapters::MariadbWrapper)
copy_dll_file(BackTestInit)
copy_config_file(BackTestInit ${CMAKE_CURRENT_SOURCE_DIR}/Configs/BackTestInit.json)


add_static_md_module(ApiBase ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/ApiBase ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/ApiBase)
target_link_libraries(ApiBaseStatic PUBLIC Spark::Network)

add_shared_module(MdApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/MdApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/MdApi)
target_link_libraries(MdApi PUBLIC QuantTradingInterface)
target_link_libraries(MdApi PRIVATE QuantTradingCommonStatic ApiBaseStatic PackagesStatic Spark::Network)

add_shared_module(MdGbkApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/MdGbkApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/MdGbkApi)
target_link_libraries(MdGbkApi PUBLIC QuantTradingInterface)
target_link_libraries(MdGbkApi PRIVATE QuantTradingCommonStatic ApiBaseStatic PackagesStatic Spark::Network Spark::Serialization)
target_compile_definitions(MdGbkApi PRIVATE MdApi_EXPORTS)


add_shared_module(TraderApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/TraderApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/TraderApi)
target_link_libraries(TraderApi PUBLIC QuantTradingInterface)
target_link_libraries(TraderApi PRIVATE QuantTradingCommonStatic ApiBaseStatic PackagesStatic Spark::Network)

add_shared_module(TraderGbkApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/TraderGbkApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/TraderGbkApi)
target_link_libraries(TraderGbkApi PUBLIC QuantTradingInterface)
target_link_libraries(TraderGbkApi PRIVATE QuantTradingCommonStatic ApiBaseStatic PackagesStatic Spark::Network Spark::Serialization)
target_compile_definitions(TraderGbkApi PRIVATE TraderApi_EXPORTS)


add_shared_module(SimExchangeApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/SimExchangeApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/SimExchangeApi)
target_link_libraries(SimExchangeApi PUBLIC QuantTradingInterface)
target_link_libraries(SimExchangeApi PRIVATE QuantTradingCommonStatic ApiBaseStatic PackagesStatic Spark::Network)

add_shared_module(SimExchangeGbkApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/SimExchangeGbkApi ${CMAKE_CURRENT_SOURCE_DIR}/src/Apis/SimExchangeGbkApi)
target_link_libraries(SimExchangeGbkApi PUBLIC QuantTradingInterface)
target_link_libraries(SimExchangeGbkApi PRIVATE QuantTradingCommonStatic ApiBaseStatic PackagesStatic Spark::Network Spark::Serialization)
target_compile_definitions(SimExchangeGbkApi PRIVATE SimExchangeApi_EXPORTS)



add_static_md_module(BackTestApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/BackTestApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/BackTestApiMiddle)
add_static_md_module(MdApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/MdApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/MdApiMiddle)
add_static_md_module(TraderApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/TraderApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/TraderApiMiddle)
add_static_md_module(SimExchangeApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/SimExchangeApiMiddle ${CMAKE_CURRENT_SOURCE_DIR}/test/ApiMiddles/SimExchangeApiMiddle)
target_link_libraries(BackTestApiMiddleStatic PUBLIC BackTest Spark::Core)
target_link_libraries(MdApiMiddleStatic PUBLIC MdApi Spark::Core)
target_link_libraries(TraderApiMiddleStatic PUBLIC TraderApi Spark::Core)
target_link_libraries(SimExchangeApiMiddleStatic PUBLIC SimExchangeApi Spark::Core)



add_application(TestBackTest ${CMAKE_CURRENT_SOURCE_DIR}/test/TestBackTest ${CMAKE_CURRENT_SOURCE_DIR}/test/TestBackTest)
target_link_libraries(TestBackTest PRIVATE QuantTradingCommonStatic PackagesStatic BackTestApiMiddleStatic Spark::Core Spark::Serialization)
copy_config_file(TestBackTest ${CMAKE_CURRENT_SOURCE_DIR}/Configs/TestBackTest.json)
copy_config_file(TestBackTest ${CMAKE_CURRENT_SOURCE_DIR}/Configs/BackTest.json)

add_application(TestMdOffer ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMdOffer ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMdOffer)
target_link_libraries(TestMdOffer PRIVATE QuantTradingCommonStatic PackagesStatic Spark::Core Spark::Serialization)
copy_config_file(TestMdOffer ${CMAKE_CURRENT_SOURCE_DIR}/Configs/TestMdOffer.json)

add_application(TestMdApi ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMdApi ${CMAKE_CURRENT_SOURCE_DIR}/test/TestMdApi)
target_link_libraries(TestMdApi PRIVATE QuantTradingCommonStatic MdApiMiddleStatic Spark::Core Spark::Serialization)
copy_config_file(TestMdApi ${CMAKE_CURRENT_SOURCE_DIR}/Configs/TestMdApi.json)

add_application(TestTraderApi ${CMAKE_CURRENT_SOURCE_DIR}/test/TestTraderApi ${CMAKE_CURRENT_SOURCE_DIR}/test/TestTraderApi)
target_link_libraries(TestTraderApi PRIVATE QuantTradingCommonStatic TraderApiMiddleStatic Spark::Core Spark::Serialization)
copy_config_file(TestTraderApi ${CMAKE_CURRENT_SOURCE_DIR}/Configs/TestTraderApi.json)

add_application(TestSimExchangeApi ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSimExchangeApi ${CMAKE_CURRENT_SOURCE_DIR}/test/TestSimExchangeApi)
target_link_libraries(TestSimExchangeApi PRIVATE QuantTradingCommonStatic SimExchangeApiMiddleStatic Spark::Core Spark::Serialization)
copy_config_file(TestSimExchangeApi ${CMAKE_CURRENT_SOURCE_DIR}/Configs/TestSimExchangeApi.json)


install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS
    QuantTradingInterface
    MdApi MdGbkApi
    TraderApi TraderGbkApi
    SimExchangeApi SimExchangeGbkApi
    BackTest
    EXPORT ${PROJECT_NAME}Targets
    #CONFIGURATIONS Release
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    "include(CMakeFindDependencyMacro)\n"
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake\")\n"
    "set(${PROJECT_NAME}_FOUND TRUE)\n"
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
