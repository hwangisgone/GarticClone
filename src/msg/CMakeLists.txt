# Add source files for the library
add_library(msg_lib STATIC 
	msg_format.cpp
	msg_sendrecv.cpp
	msg_serialize.cpp

	types/msg_connect.cpp
)

# To include msg_format.hpp
# target_include_directories(msg_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")