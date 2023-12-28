add_library(msg_factory_lib STATIC
	msg_factory.cpp
)

# Include subdirectories
add_subdirectory(new)
add_subdirectory(lobby)
add_subdirectory(room)
add_subdirectory(ingame)
add_subdirectory(leaderboard)