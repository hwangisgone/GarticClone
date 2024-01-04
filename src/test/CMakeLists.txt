add_executable(FuckClient main_client.cpp)
target_link_libraries(FuckClient PRIVATE 
	consts_lib
	client_base_lib

	client_auth_lib
	client_lobby_lib
	client_room_lib
	client_ingame_lib
	client_leaderboard_lib
	debug_lib
)

add_executable(ServerAuth main_server.cpp)
target_link_libraries(ServerAuth PRIVATE 
	consts_lib
	server_base_lib

	server_room_lib
	server_ingame_lib
	server_leaderboard_lib
	debug_lib
)
