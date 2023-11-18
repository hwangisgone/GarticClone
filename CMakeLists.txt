# CMake minimum version
cmake_minimum_required(VERSION 3.22)

# Project name
project(GarticClone)

# Add executable
add_executable(GarticExecutable src/main.cpp)


configure_file(src/wordlist.txt
    ${CMAKE_CURRENT_BINARY_DIR}/wordlist.txt COPYONLY)