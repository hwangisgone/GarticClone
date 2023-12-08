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

# Include the current directory for header files
# target_include_directories(server_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})