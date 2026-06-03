
add_subdirectory(TestMdApi)
add_subdirectory(TestSimExchangeApi)
add_subdirectory(TestBackTest)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif()
