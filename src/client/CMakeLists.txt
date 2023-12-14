set(CLIENT_SOURCES
	main.cpp

	states/client_handler.cpp

	states/state_room.cpp
	states/state_ingame.cpp
	states/state_leaderboard.cpp
	# Add more files as needed
)

add_executable(client_program ${CLIENT_SOURCES})

# Linking
target_link_libraries(client_program sockaddr_util_lib msg_lib)


# Include the current directory for header files
# target_include_directories(client_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy to outside
add_custom_command(TARGET client_program POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_program> ${CMAKE_SOURCE_DIR}/build/client_program
)