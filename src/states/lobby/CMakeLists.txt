# Add source files for the library
add_library(client_lobby_lib STATIC
	msg_lobby.cpp
	client_lobby.cpp
)

add_library(server_lobby_lib STATIC
	msg_lobby.cpp
)

add_subdirectory(test)
