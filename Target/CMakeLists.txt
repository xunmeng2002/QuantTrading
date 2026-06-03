
add_subdirectory(Init)
add_subdirectory(MdOffer)
add_subdirectory(BackTest)
add_subdirectory(BackTestDBInit)
add_subdirectory(SimExchange)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif()
