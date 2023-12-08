set(CLIENT_SOURCES
	main.cpp
	# Add more files as needed
)

add_executable(client_program ${CLIENT_SOURCES})

# Linking
target_link_libraries(client_program sockaddr_util_lib msg_lib)


# Include the current directory for header files
# target_include_directories(client_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})