add_library(js_io_lib STATIC
	js_io/exposed_input.cpp
	js_io/js_output.cpp
)
target_include_directories(js_io_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(js_io_lib PUBLIC webview_lib client_base_lib)
