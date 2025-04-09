set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Test)

function(register_test file)
    set(fileName "")
    get_filename_component(fileName ${file} NAME_WE)

    if (fileName MATCHES ".*ITest$") # Integration tests
        set(testName "IT_${fileName}")
        message(STATUS "Adding integration test ${file} with name ${testName}")
    elseif(fileName MATCHES ".*UTest$") # Unit tests
        set(testName "UT_${fileName}")
        message(STATUS "Adding unit test ${file} with name ${testName}")
    else()
        message(FATAL_ERROR "Test file ${file} does not match any naming convention")
    endif()

    add_executable(${testName} ${file})
    add_test(NAME ${testName} COMMAND ${testName})
    target_include_directories(${testName} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${testName}
            PRIVATE
            Qt6::Test
            app
    )
endfunction()

add_subdirectory(unit)
add_subdirectory(integration)
