# Add source files for the library
add_library(server_base_lib STATIC 
	server/room_handler.cpp
	server/server_lobby.cpp
	server/server_init.cpp
)

target_include_directories(server_base_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server_base_lib
PUBLIC 
	msg_lib
	debug_lib
	utils_lib
	sockaddr_util_lib

	server_auth_lib
	msg_lobby_lib
)