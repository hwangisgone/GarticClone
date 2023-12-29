# Server
# add_executable(test_sql main.cpp)
# target_link_libraries(test_sql PRIVATE SQLite::SQLite3)


add_library(text_db_lib STATIC
	textdatabase.cpp
)
