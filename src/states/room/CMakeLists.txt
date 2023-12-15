# Add source files for the library
add_library(client_room_lib STATIC
	msg_connection.cpp
	msg_start.cpp
	client_room.cpp
)

add_library(server_room_lib STATIC
	msg_connection.cpp
	msg_start.cpp
	room_room.cpp
)