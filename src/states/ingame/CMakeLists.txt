# Add source files for the library
add_library(msg_ingame_lib STATIC
	ingame/msg/msg_ingame.cpp
	ingame/msg/msg_next_end.cpp
)
target_include_directories(msg_ingame_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_ingame_lib PUBLIC msg_lib msg_room_lib)


# Client
add_library(client_ingame_lib STATIC
	ingame/client_ingame.cpp
)
target_link_libraries(client_ingame_lib 
	PRIVATE msg_ingame_lib js_io_lib client_room_lib
	PUBLIC client_base_lib
)


# Server
add_library(server_ingame_lib STATIC
	ingame/room_ingame.cpp
)
target_link_libraries(server_ingame_lib 
	PRIVATE msg_ingame_lib 
	timer_thread_lib
	rng_lib 
	text_db_lib 
	server_room_lib
	server_base_lib 
)
