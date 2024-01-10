add_executable(testDB DatabaseForPlayers.cpp)
target_link_libraries(testDB PRIVATE SQLite::SQLite3)

add_custom_command(TARGET testDB POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy $<TARGET_FILE:testDB> ${CMAKE_BINARY_DIR}/testDB
)