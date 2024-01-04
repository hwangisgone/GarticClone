# Add source files for the library
add_library(msg_auth_lib STATIC 
	auth/msg/msg_auth.cpp
)
target_include_directories(msg_auth_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(msg_auth_lib PUBLIC msg_lib)


# Client
add_library(client_auth_lib STATIC 
	auth/client_auth.cpp
)
target_link_libraries(client_auth_lib 
	PRIVATE msg_auth_lib js_io_lib
	PUBLIC client_base_lib
)


# Server
add_library(server_auth_lib STATIC
	auth/server_auth.cpp
)
# Include header file
target_include_directories(server_auth_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(server_auth_lib 
	PRIVATE msg_auth_lib 
	PUBLIC types_lib text_db_lib
)

# Testing
# add_subdirectory(test)