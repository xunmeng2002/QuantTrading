SET(PROJECT_NAME "BackTestDBInit")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(DBWriter ../BackTest/DB/DBWriter)
add_package(InitMdb ../BackTest/DB/InitMdb)
add_package(Mdb ../BackTest/DB/Mdb)

#include_package(MysqlConnector ${LibsPath}/MysqlConnector/9.0.0/include)
#include_package(duckdb ${LibsPath}/duckdb/include)

link_directories(${LibsPath}/PersonalLib/win64)
#link_directories(${LibsPath}/MysqlConnector/9.0.0)
#link_directories(${LibsPath}/MysqlConnector/9.0.0/win64/Debug)
#if(CMAKE_BUILD_TYPE MATCHES "Debug")
#	link_directories(${LibsPath}/duckdb/win64/Debug)
#else(CMAKE_BUILD_TYPE MATCHES "Debug")
#	link_directories(${LibsPath}/duckdb/win64/Release)
#endif()

add_executable(${PROJECT_NAME} ${all_file})

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib pthread)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${LibsPath}/PersonalLib/win64/PersonalLib.dll" "${CMAKE_CURRENT_BINARY_DIR}/PersonalLib.dll" COPYONLY)
endif()
