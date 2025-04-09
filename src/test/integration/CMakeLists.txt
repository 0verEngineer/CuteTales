
file(GLOB_RECURSE files "${CMAKE_CURRENT_SOURCE_DIR}/*ITest.cpp")
message(integration test files: " ${files}")

foreach(file ${files})
    register_test(${file})
endforeach()
