# Client
add_executable(client_lobby client.cpp)
# Linking
target_link_libraries(client_lobby
	client_base_lib
	msg_lib
	msg_factory_lib

	client_lobby_lib	

	sockaddr_util_lib
)


# Server
add_executable(server_lobby server.cpp)
# Linking
target_link_libraries(server_program 
	server_base_lib
	msg_lib
	msg_factory_lib

	server_lobby_lib

	sockaddr_util_lib
)