add_library(timer_thread_lib STATIC
	timer/timer_thread.cpp
)

target_include_directories(timer_thread_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(timer_thread_lib
	PRIVATE server_leaderboard_lib server_ingame_lib
	PUBLIC server_base_lib	# Public means implementation & header needs it
)