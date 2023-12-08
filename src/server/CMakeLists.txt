set(SERVER_SOURCES
	main.cpp
	server_lobby.cpp

	states/room_handler.cpp

	states/state_room.cpp
	states/state_ingame.cpp
	states/state_leaderboard.cpp
	# Add more files as needed
)

add_executable(server_program ${SERVER_SOURCES})

# Linking
target_link_libraries(server_program sockaddr_util_lib msg_lib)

# Copy to outside
add_custom_command(TARGET server_program POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:server_program> ${CMAKE_SOURCE_DIR}/build/server_program
)