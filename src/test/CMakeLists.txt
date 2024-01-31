add_executable(CmdClient cmd_client.cpp)
target_link_libraries(CmdClient PRIVATE 
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

add_executable(RunServer main_server.cpp)
target_link_libraries(RunServer PRIVATE 
	consts_lib
	server_base_lib

	server_room_lib
	server_ingame_lib
	server_leaderboard_lib
	debug_lib
)

add_custom_command(TARGET RunServer POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:RunServer> ${CMAKE_BINARY_DIR}/RunServer
)

add_custom_command(TARGET CmdClient POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:CmdClient> ${CMAKE_BINARY_DIR}/CmdClient
)

# Copy every .test.txt file to binary for use
add_custom_target(copy-runtime-files ALL
	COMMAND ${CMAKE_COMMAND} 
	-E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/txt ${CMAKE_BINARY_DIR}/txt)