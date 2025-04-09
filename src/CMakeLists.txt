
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# First the whole Application as static library
add_subdirectory(app)

# Then the executable
add_subdirectory(executable)

# Then testing
add_subdirectory(test)
