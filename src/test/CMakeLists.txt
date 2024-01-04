add_executable(FuckClient cmd_client.cpp)
target_link_libraries(FuckClient PRIVATE 
	consts_lib
	client_base_lib

	client_auth_lib
	client_lobby_lib
	client_room_lib
	client_ingame_lib
	client_leaderboard_lib
	debug_lib

	auto_io_lib
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

add_custom_command(TARGET ServerAuth POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:ServerAuth> ${CMAKE_BINARY_DIR}/ServerAuth
)

add_custom_command(TARGET FuckClient POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:FuckClient> ${CMAKE_BINARY_DIR}/FuckClient
)

# Copy every .test.txt file to binary for use
add_custom_target(copy-runtime-files ALL
	COMMAND ${CMAKE_COMMAND} 
	-E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/txt ${CMAKE_BINARY_DIR}/txt)