SET(PROJECT_NAME "TestSimExchangeApi")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(SimExchangeApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/SimExchangeApiMiddle)
add_package(ServerConfig ${CMAKE_SOURCE_DIR}/Source/ServerConfig)


include_package(SimExchangeApi ${CMAKE_SOURCE_DIR}/../Libs/QuantTrading/include)

link_directories(${CMAKE_SOURCE_DIR}/../Libs/QuantTrading)

add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib SimExchangeApi.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib SimExchangeApi)
endif()


IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${LibsPath}/PersonalLib/win64/PersonalLib.dll" "${CMAKE_CURRENT_BINARY_DIR}/PersonalLib.dll" COPYONLY)

	add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "$<TARGET_FILE:SimExchangeApi>" 
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:SimExchangeApi>"
        COMMENT "Copying SimExchangeApi.dll DLL...")
endif()