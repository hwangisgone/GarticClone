# Add source files for the library
add_library(msg_lobby_lib STATIC
	lobby/msg/msg_lobby.cpp
)
target_include_directories(msg_lobby_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_lobby_lib PUBLIC msg_lib types_lib)


# Client
add_library(client_lobby_lib STATIC
	lobby/client_lobby.cpp
)
target_link_libraries(client_lobby_lib 
	PRIVATE msg_lobby_lib js_io_lib
)


# add_subdirectory(test)
