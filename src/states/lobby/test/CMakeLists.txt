# Client
add_executable(client_lobby client.cpp)
# Linking
target_link_libraries(client_lobby PRIVATE master_client_lib input_testing_lib)


# Server
add_executable(server_lobby server.cpp)
# Linking
target_link_libraries(server_lobby PRIVATE master_server_lib)


# Copy to outside
add_custom_command(TARGET client_lobby POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:client_lobby> ${CMAKE_SOURCE_DIR}/build/client_lobby
)

add_custom_command(TARGET server_lobby POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:server_lobby> ${CMAKE_SOURCE_DIR}/build/server_lobby
)