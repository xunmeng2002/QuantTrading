SET(PROJECT_NAME "TestSimExchangeApi")
SET(APIVersion "6.7.9")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(Config ./Config)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(SimExchangeApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/SimExchangeApiMiddle)
add_package(ServerConfig ${CMAKE_SOURCE_DIR}/Source/ServerConfig)
add_package(Environment ${CMAKE_SOURCE_DIR}/Source/Environment)

include_directories(${LibsPath}/CTP/${APIVersion}/include)

add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} Spark.lib SimExchangeApi.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} Spark SimExchangeApi)
endif()


IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${CMAKE_SOURCE_DIR}/Configs/TestSimExchangeApi.json" "${CMAKE_CURRENT_BINARY_DIR}/TestSimExchangeApi.json" COPYONLY)
endif()
