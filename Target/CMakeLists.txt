include_package(PersonalLib ${CMAKE_SOURCE_DIR}/../Libs/PersonalLib/include)
link_directories(${CMAKE_SOURCE_DIR}/../Libs/PersonalLib/win64)

add_subdirectory(MdOffer)
add_subdirectory(BackTest)
add_subdirectory(InitBackTestDB)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif()
