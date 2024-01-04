# Add source files for the library
add_library(client_base_lib STATIC 
	client/client_handler.cpp
	client/client_init.cpp
)

target_include_directories(client_base_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(client_base_lib PUBLIC 
	msg_lib
	debug_lib
)