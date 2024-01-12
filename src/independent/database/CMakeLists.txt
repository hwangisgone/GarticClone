# Server
# add_executable(test_sql main.cpp)
# target_link_libraries(test_sql PRIVATE SQLite::SQLite3)


add_library(text_db_lib STATIC
	database/textdatabase.cpp
	database/word_list.cpp
)

target_include_directories(text_db_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(text_db_lib 
	PRIVATE rng_lib 	# Private means only implementation needs it
	PUBLIC types_lib
)


configure_file(database/accounts.txt ${CMAKE_BINARY_DIR}/txt/accounts.txt COPYONLY)
configure_file(database/word.txt ${CMAKE_BINARY_DIR}/txt/word.txt COPYONLY)
