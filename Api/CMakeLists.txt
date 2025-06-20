include_package(PersonalLib ${CMAKE_SOURCE_DIR}/../Libs/PersonalLib/include)
link_directories(${CMAKE_SOURCE_DIR}/../Libs/PersonalLib/win64)

add_subdirectory(MdApi)
add_subdirectory(MdCApi)
add_subdirectory(MdUtf8CApi)
add_subdirectory(TradeApi)
add_subdirectory(TradeCApi)
add_subdirectory(TradeUtf8CApi)

add_subdirectory(SimExchangeApi)
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
endif()
