SET(PROJECT_NAME "TestMdApi")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(Config ./Config)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(MdApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/MdApiMiddle)
add_package(ServerConfig ${CMAKE_SOURCE_DIR}/Source/ServerConfig)


add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} Spark.lib MdApi.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} Spark MdApi)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${CMAKE_SOURCE_DIR}/Configs/TestMdApi.json" "${CMAKE_CURRENT_BINARY_DIR}/TestMdApi.json" COPYONLY)
endif()
