SET(PROJECT_NAME "TestMdApi")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(Config ./Config)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(MdApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/MdApiMiddle)
add_package(ServerConfig ${CMAKE_SOURCE_DIR}/Source/ServerConfig)


include_package(MdApi ${CMAKE_SOURCE_DIR}/../Libs/QuantTrading/include)

link_directories(${CMAKE_SOURCE_DIR}/../Libs/QuantTrading)

add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib MdApi.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib MdApi)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${CMAKE_SOURCE_DIR}/Configs/TestMdApi.json" "${CMAKE_CURRENT_BINARY_DIR}/TestMdApi.json" COPYONLY)

	configure_file("${LibsPath}/PersonalLib/win64/PersonalLib.dll" "${CMAKE_CURRENT_BINARY_DIR}/PersonalLib.dll" COPYONLY)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:MdApi>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:MdApi>" COMMENT "Copying MdApi.dll DLL...")
endif()