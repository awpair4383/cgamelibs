#include "GLFW/glfw3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cgamelibs.h"

/**
 * @brief Initializes GLFW and creates the window.
 * @param window A pointer to the GLFW window pointer to be initialized.
 */
void init_window(Window *const window, const uint16_t wPx, const uint16_t hPx) { // should handle a maximum of 65535 X 65535, consider making these floats for subpixel precision/rendering.
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Tell GLFW not to create an OpenGL context since we are using Vulkan
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    // We disable resizing for simplicity, as handling window resizing is complex in Vulkan
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Create the window
    window->glfwWindow = glfwCreateWindow(wPx, hPx, "Vulkan Hello World", NULL, NULL);
    glfwSetWindowSize(window->glfwWindow, wPx, hPx);
    
    if (!window->glfwWindow) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    printf("GLFW window created successfully.\n");
}

/**
 * @brief Destroys the GLFW window and terminates the GLFW library.
 *
 * This function releases all resources associated with the GLFW window
 * and then terminates the GLFW library, which must be the last step
 * of any GLFW cleanup.
 *
 * @param window Pointer to the `Window` struct containing the GLFW 
 * window handle (`glfwWindow`).
 */
void deinit_window(Window *const window){
    // 1. Destroy the specific window handle
    if (window->glfwWindow) {
        glfwDestroyWindow(window->glfwWindow);
        window->glfwWindow = NULL; // Optional: Null the pointer
        printf("GLFW window destroyed.\n");
    }

    // 2. Terminate the GLFW library (releases internal resources)
    glfwTerminate();
    printf("GLFW terminated.\n");
}