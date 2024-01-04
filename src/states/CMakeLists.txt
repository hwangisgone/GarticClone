add_library(master_server_lib INTERFACE)
target_link_libraries(master_server_lib INTERFACE
	server_room_lib
	server_ingame_lib
	server_leaderboard_lib
)

# Include subdirectories
add_subdirectory(auth)
add_subdirectory(lobby)
add_subdirectory(room)
add_subdirectory(ingame)
add_subdirectory(leaderboard)