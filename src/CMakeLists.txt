# Include the root directory for network_constants.h & debugging.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include subdirectories
add_subdirectory(database)
add_subdirectory(in_out)

add_subdirectory(sockaddr_in)
add_subdirectory(msg)
add_subdirectory(states)
add_subdirectory(server)
add_subdirectory(client)

# Generate master client and master server library
# As stupid as it may sound, the msg_factory_lib prevent others from generating just becuase it makes the unique_ptr
# TODO: deal with this issue?
add_library(master_client_lib INTERFACE)
target_link_libraries(master_client_lib INTERFACE
	client_base_lib
	msg_lib
	msg_factory_lib

	client_auth_lib
	client_lobby_lib
	client_room_lib
	client_ingame_lib
	client_leaderboard_lib

	sockaddr_util_lib
)

# IMPORTANT NOTE: TO LINK CORRECTLY, DEPENDENCIES MUST BE LINKED LATER.
# MUST BE LINKED IN ORDER OF FORWARD DECLARATION
# E.G. B needs A
#	class A; in B
# LINKING ORDER:
#	B_lib
#	A_lib

add_library(master_server_lib INTERFACE)
target_link_libraries(master_server_lib INTERFACE
	server_base_lib
	msg_lib
	msg_factory_lib

	server_auth_lib
	server_lobby_lib
	server_room_lib
	server_ingame_lib
	server_leaderboard_lib

	text_db_lib

	sockaddr_util_lib
)



# GUI
add_library(webview_lib INTERFACE ../libs/webview/webview.cc)

# Check the target system
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK REQUIRED IMPORTED_TARGET "gtk+-3.0")
	pkg_check_modules(WEBKIT REQUIRED IMPORTED_TARGET "webkit2gtk-4.0")

	message(STATUS "Configuring for Linux")
	target_compile_options(webview_lib INTERFACE -std=c++11 -Ilibs/webview)
	target_link_libraries(webview_lib INTERFACE PkgConfig::GTK PkgConfig::WEBKIT)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Configuring for Windows")
	target_compile_options(webview_lib INTERFACE -std=c++14 -mwindows -Ilibs/webview -Ilibs/webview2/build/native/include -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	message(STATUS "Configuring for macOS")
	target_compile_options(webview_lib INTERFACE -std=c++11 -Ilibs/webview -framework WebKit)
else()
	message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()


# Read the content of the HTML file and generate a C++ source file
file(READ "../ui/dist/index.html" HTML_CONTENT)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/html_const.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/html_const.cpp" @ONLY)
message(STATUS "Read the HTML file")


# Append HTML to file
add_executable(CharadeioClient bind.cc "${CMAKE_CURRENT_BINARY_DIR}/html_const.cpp")
target_include_directories(CharadeioClient PRIVATE "../libs/webview/")

target_link_libraries(CharadeioClient PRIVATE 
	master_client_lib
	webview_lib
)