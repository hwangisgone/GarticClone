# Header only library
add_library(utils_lib INTERFACE)
target_include_directories(utils_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_library(consts_lib INTERFACE)
target_include_directories(consts_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/consts)

add_library(types_lib INTERFACE)
target_include_directories(types_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/types)

# Others
add_library(rng_lib STATIC utils/utils/rng.cpp)
target_include_directories(rng_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utils)