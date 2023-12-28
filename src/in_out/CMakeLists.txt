add_library(js_io_lib STATIC
	exposed_input.cpp
	js_output.cpp
)
target_link_libraries(js_io_lib PRIVATE webview_lib)


add_library(cmd_io_lib STATIC
	test_input.cpp
)