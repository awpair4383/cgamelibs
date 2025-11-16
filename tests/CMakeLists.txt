cmake_minimum_required(VERSION 3.10)
project(cgamelibs)

# Add the test executable
add_executable(test_cgamelibs test_cgamelibs.c)

# Link the library
target_link_libraries(test_cgamelibs PRIVATE cgamelibs)

# Specify the include directories for the test
target_include_directories(test_cgamelibs PRIVATE ../include)

# Enable testing
enable_testing()

# Optionally, add custom target to run tests
add_test(NAME test_cgamelibs COMMAND test_cgamelibs)

# Function to add test executables
function(add_test_executable test_name source_file)
    # Add the test executable
    add_executable(${test_name} ${source_file})

    # Link the library
    target_link_libraries(${test_name} PRIVATE cgamelibs)

    # Specify the include directories for the test
    target_include_directories(${test_name} PRIVATE ../include)

    # Optionally, add a custom target to run tests
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_test_executable(test_hashtable test_hashtable.c)

# Set AddressSanitizer flags for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Enable AddressSanitizer
    target_compile_options(test_cgamelibs PRIVATE -fsanitize=address)
    target_link_libraries(test_cgamelibs PRIVATE -fsanitize=address)

    target_compile_options(test_hashtable PRIVATE -fsanitize=address)
    target_link_libraries(test_hashtable PRIVATE -fsanitize=address)
endif()
