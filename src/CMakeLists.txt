# Include the root directory for network_constants.h & debugging.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include subdirectories
add_subdirectory(database)

add_subdirectory(sockaddr_in)
add_subdirectory(msg)
add_subdirectory(states)
add_subdirectory(server)
add_subdirectory(client)

# Generate master client and master server library
# As stupid as it may sound, the msg_factory_lib prevent others from generating just becuase it makes the unique_ptr
# TODO: deal with this issue?
add_library(master_client_lib INTERFACE)
target_link_libraries(master_client_lib INTERFACE
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

add_library(master_server_lib INTERFACE)
target_link_libraries(master_server_lib INTERFACE
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


# Client
add_executable(client_program client/main.cpp)
target_link_libraries(client_program PRIVATE master_client_lib)

# Server
add_executable(server_program server/main.cpp)
target_link_libraries(server_program PRIVATE master_server_lib)


# Copy to outside
#add_custom_command(TARGET client_program POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_program> ${CMAKE_SOURCE_DIR}/build/client_program
#)





