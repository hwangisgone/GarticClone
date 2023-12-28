# Server
add_executable(test_sql main.cpp)
target_link_libraries(test_sql PRIVATE SQLite3::SQLite3)

