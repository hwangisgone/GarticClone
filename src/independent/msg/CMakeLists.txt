# Add source files for the library
add_library(msg_base_lib STATIC 
	msg/type/msg_base.cpp
	msg/type/msg_factory.cpp
	msg/type/msg_serialize.cpp
)

target_include_directories(msg_base_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_base_lib 
PRIVATE
	msg_auth_lib
	msg_lobby_lib
	msg_room_lib
	msg_ingame_lib
	msg_leaderboard_lib
PUBLIC 
	debug_lib
)


add_library(msg_lib STATIC 
	msg/msg_sendrecv.cpp
)

target_include_directories(msg_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_lib PUBLIC msg_base_lib)