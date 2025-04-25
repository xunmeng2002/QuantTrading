SET(PROJECT_NAME "TestMdApi")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
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
