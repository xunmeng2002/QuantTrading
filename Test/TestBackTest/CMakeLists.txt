SET(PROJECT_NAME "TestBackTest")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(TestUtility ${CMAKE_SOURCE_DIR}/Test/Source/TestUtility)
add_package(BackTestApiMiddle ${CMAKE_SOURCE_DIR}/Test/Source/BackTestApiMiddle)


include_package(BackTest ${CMAKE_SOURCE_DIR}/../Libs/QuantTrading/include)

link_directories(${CMAKE_SOURCE_DIR}/../Libs/QuantTrading)

add_executable(${PROJECT_NAME} ${all_file})

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib BackTest.lib)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib BackTest)
endif()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
	configure_file("${LibsPath}/PersonalLib/win64/PersonalLib.dll" "${CMAKE_CURRENT_BINARY_DIR}/PersonalLib.dll" COPYONLY)
endif()