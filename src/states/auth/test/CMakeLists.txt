# Client
# add_executable(client_auth client.cpp)
# Linking
# target_link_libraries(client_auth PRIVATE debug_lib master_client_lib cmd_io_lib)


# Server
add_executable(server_auth server.cpp)
# Linking
target_link_libraries(server_auth PRIVATE 
	debug_lib 
	server_base_lib
	master_server_lib 
	consts_lib
)


# Copy to outside
#[[
add_custom_command(TARGET client_auth POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:client_auth> ${CMAKE_SOURCE_DIR}/build/client_auth
)
]]

add_custom_command(TARGET server_auth POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:server_auth> ${CMAKE_SOURCE_DIR}/build/server_auth 
)