# Add source files for the library
add_library(client_auth_lib STATIC 
	msg_auth.cpp
	client_auth.cpp
)

add_library(server_auth_lib STATIC
	msg_auth.cpp
)