#[[ # Not added as of yet
# QT Related
find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)


qt_add_executable(myapp
	main.cpp
)

qt_add_qml_module(myapp
	URI hello
	VERSION 1.0
	QML_FILES 
		main.qml
)

target_link_libraries(myapp PRIVATE 
	Qt6::Gui 
	Qt6::Quick
	Serializer
)
]]

# Include the root directory for network_constants.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Include subdirectories
add_subdirectory(sockaddr_in)
add_subdirectory(msg)
add_subdirectory(server)
add_subdirectory(client)





