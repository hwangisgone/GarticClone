# Header only library
add_library(debug_lib STATIC printdebug/debugging.cpp)
target_include_directories(debug_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# file(GENERATE OUTPUT what.txt CONTENT "$<$<CONFIG:Release>:NDEBUG>")

# Set by -D CMAKE_BUILD_TYPE=Debug
target_compile_definitions(debug_lib INTERFACE 
	$<$<CONFIG:Release>:NDEBUG>
	$<$<CONFIG:Testing>:TEST_ENABLED>
)