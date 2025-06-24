SET(PROJECT_NAME "BackTestDBInit")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(DBOperate ../BackTest/DB/DBOperate)
add_package(InitMdb ../BackTest/DB/InitMdb)
add_package(Mdb ../BackTest/DB/Mdb)

#include_package(MysqlConnector ${CMAKE_SOURCE_DIR}/../Libs/MysqlConnector/9.0.0/include)
#include_package(duckdb ${CMAKE_SOURCE_DIR}/../Libs/duckdb/include)

#link_directories(${CMAKE_SOURCE_DIR}/../Libs/MysqlConnector/9.0.0)
#link_directories(${CMAKE_SOURCE_DIR}/../Libs/MysqlConnector/9.0.0/Debug)
#if(CMAKE_BUILD_TYPE MATCHES "Debug")
#	link_directories(${CMAKE_SOURCE_DIR}/../Libs/duckdb/win64/Debug)
#else(CMAKE_BUILD_TYPE MATCHES "Debug")
#	link_directories(${CMAKE_SOURCE_DIR}/../Libs/duckdb/win64/Release)
#endif()

add_executable(${PROJECT_NAME} ${all_file})

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib pthread)
endif()
