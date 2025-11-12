#include "cgamelibs.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initializes the Vulkan surface for the specified window.
 *
 * This function uses GLFW's built-in method to create a Vulkan surface 
 * associated with the given `Window` struct. The resulting surface handle 
 * is stored in the `vkSurfaceKHR` member of the `Window` struct.
 *
 * If the surface creation fails, an error message is printed to stderr, 
 * and the program exits.
 *
 * @param window Pointer to a `Window` struct that contains the GLFW 
 *               window handle and the Vulkan instance required for surface 
 *               creation. The function modifies the `vkSurfaceKHR` member 
 *               to store the created surface handle.
 */
void init_surface(Window *const window) {
    // GLFW has a built-in function to create a surface from the window
    int retval = glfwCreateWindowSurface(window->vkInstance, window->glfwWindow, NULL, &window->vkSurfaceKHR);
    if (retval != VK_SUCCESS) {
        fprintf(stderr, "Failed to create window surface!\nReason: %d\n", retval);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Cleans up and destroys the Vulkan surface associated with the window.
 *
 * This function uses vkDestroySurfaceKHR to release the resources held by 
 * the Vulkan surface handle stored in the `Window` struct. This must be 
 * called before the Vulkan instance itself is destroyed.
 *
 * @param window Pointer to the `Window` struct containing the Vulkan 
 * instance (`vkInstance`) and the surface handle 
 * (`vkSurfaceKHR`) to be destroyed.
 */
void deinit_surface(Window *const window) {
    // The surface is an object of the Instance. 
    // It must be destroyed before the Instance is destroyed.
    vkDestroySurfaceKHR(window->vkInstance, window->vkSurfaceKHR, NULL);
    
    // Optional: Set the handle to VK_NULL_HANDLE after destruction 
    // to prevent accidental use (often a good practice).
    window->vkSurfaceKHR = VK_NULL_HANDLE; 
}