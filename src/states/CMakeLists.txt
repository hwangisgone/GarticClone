add_library(msg_factory_lib STATIC
	msg_factory.cpp
)

add_library(input_testing_lib STATIC
	test_input.cpp

)

# Include subdirectories
add_subdirectory(new)
add_subdirectory(lobby)
add_subdirectory(room)
add_subdirectory(ingame)
add_subdirectory(leaderboard)