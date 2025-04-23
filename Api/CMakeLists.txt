include_package(PersonalLib ${CMAKE_SOURCE_DIR}/../Libs/PersonalLib/include)

add_subdirectory(MdApi)
#add_subdirectory(MdCApi)
#add_subdirectory(MdUtf8CApi)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif()
