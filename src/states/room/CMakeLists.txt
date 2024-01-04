# Add source files for the library
add_library(msg_room_lib STATIC
	room/msg/msg_connection.cpp
	room/msg/msg_start.cpp
)
target_include_directories(msg_room_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_room_lib PUBLIC msg_lib)


# Client
add_library(client_room_lib STATIC
	room/client_room.cpp
)
target_link_libraries(client_room_lib 
	PRIVATE msg_room_lib js_io_lib
	PUBLIC client_base_lib 
)


# Server
add_library(server_room_lib STATIC
	room/room_room.cpp
)
target_link_libraries(server_room_lib 
	PRIVATE msg_room_lib
	PUBLIC server_base_lib
)