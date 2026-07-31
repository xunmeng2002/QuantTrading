SET(PROJECT_NAME "TestBackTest")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(Config ./Config)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(BackTestApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/BackTestApiMiddle)


include_directories(${LibsPath}/QuantTrading/include)

link_directories(${LibsPath}/Spark/win64)
link_directories(${LibsPath}/QuantTrading)

add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} Spark.lib BackTest.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} Spark BackTest)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${CMAKE_SOURCE_DIR}/Configs/TestBackTest.json" "${CMAKE_CURRENT_BINARY_DIR}/TestBackTest.json" COPYONLY)
	configure_file("${CMAKE_SOURCE_DIR}/Configs/BackTest.json" "${CMAKE_CURRENT_BINARY_DIR}/BackTest.json" COPYONLY)
endif()
