cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(cgamelibs C)

# Specify the source files
set(SOURCES
    src/cgamelibs.c
    src/render/devices.c
    src/render/window.c
)

# Specify the header files (if any)
set(HEADERS
    include/cgamelibs.h
)

# Find Vulkan package
find_package(Vulkan REQUIRED)

# Check for Wayland support
find_package(Wayland QUIET)

if(Wayland_FOUND)
    message(FATAL_ERROR "Wayland support is not allowed. Please disable Wayland support.")
endif()

# Create the library
add_library(cgamelibs STATIC ${SOURCES} ${HEADERS})

# Find Vulkan
find_package(Vulkan REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

# Specify the include directory for this library
target_include_directories(cgamelibs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${Vulkan_INCLUDE_DIRS}  # Include Vulkan headers
    ${glfw3_INCLUDE_DIRS}
)

# Link Vulkan library
target_link_libraries(cgamelibs PUBLIC ${Vulkan_LIBRARIES} glfw)

# Optionally, set the C standard
set_target_properties(cgamelibs PROPERTIES
    C_STANDARD 99        # Set to C11 if needed
    C_STANDARD_REQUIRED True
)

enable_testing()

# Add the tests subdirectory
add_subdirectory(tests)
