# Add source files for the library
add_library(client_ingame_lib STATIC
	msg_ingame.cpp
	msg_next_end.cpp
	client_ingame.cpp
)

add_library(server_ingame_lib STATIC
	msg_ingame.cpp
	msg_next_end.cpp
	room_ingame.cpp
)