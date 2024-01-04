# Add source files for the library
add_library(msg_leaderboard_lib STATIC
	leaderboard/msg/msg_leaderboard.cpp
)
target_include_directories(msg_leaderboard_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_leaderboard_lib PUBLIC msg_lib)


# Client
add_library(client_leaderboard_lib STATIC
	leaderboard/client_leaderboard.cpp
)
target_link_libraries(client_leaderboard_lib 
	PRIVATE client_base_lib msg_leaderboard_lib
)


# Server
add_library(server_leaderboard_lib STATIC
	leaderboard/room_leaderboard.cpp
)
target_link_libraries(server_leaderboard_lib 
	PRIVATE server_base_lib msg_leaderboard_lib
)