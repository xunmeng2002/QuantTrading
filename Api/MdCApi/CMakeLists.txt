SET(PROJECT_NAME "MdCApi")
project(${PROJECT_NAME})
message("PROJECT_NAME:" ${PROJECT_NAME})

add_package(Src ./Src)
add_package(ApiBase ../ApiBase)
add_package(Config ../Config)
add_package(MdApi ../MdApi/Src)
add_package(Packages ${CMAKE_SOURCE_DIR}/Source/Packages)
add_package(Version ${CMAKE_SOURCE_DIR}/Source/Version)
add_package(Error ${CMAKE_SOURCE_DIR}/Source/Error)


include_package(OpensslLib ${CMAKE_SOURCE_DIR}/../Libs/openssl/3.0.5/include)

add_definitions(-DLIB_MD_CAPI_EXPORT)
add_definitions(-DLIB_MD_API_EXPORT)


if(${CMAKE_CL_64})
	link_directories(${CMAKE_SOURCE_DIR}/../Libs/openssl/3.0.5/win64_2022)
else(${CMAKE_CL_64})
	link_directories(${CMAKE_SOURCE_DIR}/../Libs/openssl/3.0.5/win32_2022)
endif(${CMAKE_CL_64})
add_library(${PROJECT_NAME} SHARED ${all_file})


if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(${PROJECT_NAME} PersonalLib.lib libcrypto_static.lib libssl_static.lib WS2_32.LIB)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries(${PROJECT_NAME} PersonalLib crypto ssl pthread dl)
endif()