# Add source files for the library
add_library(client_auth_lib STATIC 
	msg_auth.cpp
	client_auth.cpp
)
target_link_libraries(client_auth_lib PRIVATE js_io_lib)

add_library(server_auth_lib STATIC
	msg_auth.cpp
)