SET(PROJECT_NAME "TestBackTest")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(Config ./Config)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(BackTestApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/BackTestApiMiddle)


include_package(BackTest ${LibsPath}/QuantTrading/include)

link_directories(${LibsPath}/PersonalLib/win64)
link_directories(${LibsPath}/QuantTrading)

add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib BackTest.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib BackTest)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${CMAKE_SOURCE_DIR}/Configs/TestBackTest.json" "${CMAKE_CURRENT_BINARY_DIR}/TestBackTest.json" COPYONLY)
	configure_file("${CMAKE_SOURCE_DIR}/Configs/BackTest.json" "${CMAKE_CURRENT_BINARY_DIR}/BackTest.json" COPYONLY)

	configure_file("${LibsPath}/PersonalLib/win64/PersonalLib.dll" "${CMAKE_CURRENT_BINARY_DIR}/PersonalLib.dll" COPYONLY)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E 
		copy_if_different "$<TARGET_FILE:BackTest>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:BackTest>" COMMENT "Copying BackTest.dll DLL...")

    configure_file("${LibsPath}/duckdb/win64/duckdb.dll" "${CMAKE_CURRENT_BINARY_DIR}/duckdb.dll" COPYONLY)
	configure_file("${LibsPath}/SQLite/3.36.0/win64/sqlite3.dll" "${CMAKE_CURRENT_BINARY_DIR}/sqlite3.dll" COPYONLY)
	configure_file("${LibsPath}/MysqlConnector/9.0.0/win64/debug/libcrypto-3-x64.dll" "${CMAKE_CURRENT_BINARY_DIR}/libcrypto-3-x64.dll" COPYONLY)
	configure_file("${LibsPath}/MysqlConnector/9.0.0/win64/debug/libssl-3-x64.dll" "${CMAKE_CURRENT_BINARY_DIR}/libssl-3-x64.dll" COPYONLY)
	configure_file("${LibsPath}/MysqlConnector/9.0.0/win64/debug/mysqlcppconn-10-vs14.dll" "${CMAKE_CURRENT_BINARY_DIR}/mysqlcppconn-10-vs14.dll" COPYONLY)
	configure_file("${LibsPath}/MysqlConnector/9.0.0/win64/debug/mysqlcppconnx-2-vs14.dll" "${CMAKE_CURRENT_BINARY_DIR}/mysqlcppconnx-2-vs14.dll" COPYONLY)
endif()