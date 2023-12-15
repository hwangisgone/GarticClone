# Add source files for the library
add_library(client_leaderboard_lib STATIC
	msg_leaderboard.cpp
	client_leaderboard.cpp
)

add_library(server_leaderboard_lib STATIC
	msg_leaderboard.cpp
	room_leaderboard.cpp
)