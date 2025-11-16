cmake_minimum_required(VERSION 3.10)
project(cgamelibs)

# ----------------------------------------------------------------------
# Library target (assumed to be defined elsewhere in the project)
# ----------------------------------------------------------------------
# add_library(cgamelibs ...)   # <-- your library definition

# ----------------------------------------------------------------------
# Helper to create a test executable and register it with CTest
# ----------------------------------------------------------------------
function(add_test_executable test_name source_file)
    add_executable(${test_name} ${source_file})
    target_link_libraries(${test_name} PRIVATE cgamelibs)
    target_include_directories(${test_name} PRIVATE ../include)

    # Apply AddressSanitizer flags for Debug builds
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${test_name} PRIVATE -fsanitize=address)
        target_link_libraries(${test_name} PRIVATE -fsanitize=address)
    endif()

    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# ----------------------------------------------------------------------
# Existing test
# ----------------------------------------------------------------------
add_test_executable(test_cgamelibs test_cgamelibs.c)

# ----------------------------------------------------------------------
# Additional tests
# ----------------------------------------------------------------------
add_test_executable(test_hashtable test_hashtable.c)
add_test_executable(test_vector   test_vector.c)   # <-- new vector test
add_test_executable(test_single_linked_list test_single_linked_list.c)