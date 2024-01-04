# Add source files for the library
add_library(sockaddr_util_lib STATIC 
	sockaddr_in/sockaddr_in_functions.cpp
)

target_include_directories(sockaddr_util_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
