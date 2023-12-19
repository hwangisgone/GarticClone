cmake_minimum_required(VERSION 3.18)

project(GarticPhone VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include subdirectories
add_subdirectory(src)



# GUI
# Read the content of the HTML file and generate a C++ source file
file(READ "../ui/dist/index.html" HTML_CONTENT)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/html_const.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/html_const.cpp" @ONLY)

message(STATUS "Read the HTML file")

# Add your main C++ source file
add_executable(CharadeioClient src/bind.cc "${CMAKE_CURRENT_BINARY_DIR}/html_const.cpp")

target_include_directories(CharadeioClient PRIVATE "libs/webview/")

# Check the target system
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK REQUIRED IMPORTED_TARGET "gtk+-3.0")
	pkg_check_modules(WEBKIT REQUIRED IMPORTED_TARGET "webkit2gtk-4.0")

	message(STATUS "Configuring for Linux")
	target_compile_options(CharadeioClient PRIVATE -std=c++11 -Ilibs/webview)
	target_link_libraries(CharadeioClient PRIVATE PkgConfig::GTK PkgConfig::WEBKIT)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "Configuring for Windows")
	target_compile_options(CharadeioClient PRIVATE -std=c++14 -mwindows -Ilibs/webview -Ilibs/webview2/build/native/include -ladvapi32 -lole32 -lshell32 -lshlwapi -luser32 -lversion)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	message(STATUS "Configuring for macOS")
	target_compile_options(CharadeioClient PRIVATE -std=c++11 -Ilibs/webview -framework WebKit)
else()
	message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()