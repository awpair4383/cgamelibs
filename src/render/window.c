#include "GLFW/glfw3.h"
#include <stdio.h>
#include <stdlib.h>

#include "cgamelibs.h"

/**
 * @brief Initializes GLFW and creates the window.
 * @param window A pointer to the GLFWwindow pointer to be initialized.
 */
void init_window(Window* window, int wPx, int hPx) {
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
