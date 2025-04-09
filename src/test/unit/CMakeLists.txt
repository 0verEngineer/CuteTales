
file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/*UTest.cpp")
message(unit test files: " ${files}")

foreach(file ${files})
    register_test(${file})
endforeach()
