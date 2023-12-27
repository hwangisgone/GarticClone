# Add source files for the library
add_library(server_base_lib STATIC 
	room_handler.cpp
	server_lobby.cpp
	server_init.cpp
	authorization.cpp
)