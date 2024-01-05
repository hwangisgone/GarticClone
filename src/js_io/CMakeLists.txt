add_library(js_io_lib STATIC
	js_io/exposed_input.cpp
	js_io/js_output.cpp
)
target_include_directories(js_io_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(js_io_lib PUBLIC webview_lib client_base_lib)


add_library(auto_io_lib STATIC
	js_io/test_input.cpp
)
target_include_directories(auto_io_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(auto_io_lib PUBLIC client_base_lib)
