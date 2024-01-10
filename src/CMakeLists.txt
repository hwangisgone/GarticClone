message(CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}")

# Find SQLite3
find_package(SQLite3 REQUIRED)

# GUI
add_library(webview_lib INTERFACE)
target_include_directories(webview_lib INTERFACE ../libs/webview)

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



add_subdirectory(server)
add_subdirectory(client)

add_subdirectory(timer)

add_subdirectory(js_io)
add_subdirectory(independent)
add_subdirectory(states)

add_subdirectory(test)
add_subdirectory(test2)