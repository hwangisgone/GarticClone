cmake_minimum_required(VERSION 3.18)

project(FUCK VERSION 1.0 LANGUAGES CXX)

add_subdirectory(src)


# Read the content of the HTML file and generate a C++ source file
file(READ "ui/dist/index.html" HTML_CONTENT)
configure_file("src/html_const.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/src/html_const.cpp" @ONLY)
message(STATUS "Read the HTML file")

# Append HTML to file
add_executable(CharadeioClient src/bind.cc "${CMAKE_CURRENT_BINARY_DIR}/src/html_const.cpp")
target_link_libraries(CharadeioClient PRIVATE 
	consts_lib
	client_base_lib
	js_io_lib

	client_auth_lib
	client_lobby_lib
	client_room_lib
	client_ingame_lib
	client_leaderboard_lib
	debug_lib
)

configure_file(database/network.db ${CMAKE_BINARY_DIR}/db/network.db COPYONLY)