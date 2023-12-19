# Include the root directory for network_constants.h & debugging.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include subdirectories
add_subdirectory(sockaddr_in)
add_subdirectory(msg)
add_subdirectory(states)
add_subdirectory(server)
add_subdirectory(client)


# Client
add_executable(client_program client/main.cpp)
# Linking
target_link_libraries(client_program 
	client_base_lib
	msg_lib
	msg_factory_lib

	client_auth_lib
	client_lobby_lib
	client_room_lib
	client_ingame_lib
	client_leaderboard_lib

	sockaddr_util_lib
)
# IMPORTANT NOTE: TO LINK CORRECTLY, DEPENDENCIES MUST BE LINKED LATER.
# MUST BE LINKED IN ORDER OF FORWARD DECLARATION
# E.G. B needs A
#	class A; in B
# LINKING ORDER:
#	B_lib
#	A_lib

# Server
add_executable(server_program server/main.cpp)
# Linking
target_link_libraries(server_program 
	server_base_lib
	msg_lib
	msg_factory_lib

	server_auth_lib
	server_lobby_lib
	server_room_lib
	server_ingame_lib
	server_leaderboard_lib

	sockaddr_util_lib
)

# Copy to outside
#add_custom_command(TARGET client_program POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_program> ${CMAKE_SOURCE_DIR}/build/client_program
#)





