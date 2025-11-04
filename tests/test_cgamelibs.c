#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "cgamelibs.h"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Function declarations
void mainLoop(GLFWwindow* window);
void cleanup(GLFWwindow* window, VkInstance instance, VkSurfaceKHR surface);
void createInstance(VkInstance *instance);
void createSurface(GLFWwindow* window, VkInstance pvkinstance, VkSurfaceKHR* surface);

int main() {
    Window window;

    VkInstance vk_instance = VK_NULL_HANDLE; // Initialize to null
    VkSurfaceKHR vk_surface = VK_NULL_HANDLE; // Initialize to null

    // 1. Initialize GLFW and create the window
    // This calls glfwInit(), which must happen before querying extensions.
    init_window(&window, 800, 600);
    
    // 2. Create the Vulkan instance
    // Now glfwGetRequiredInstanceExtensions will work correctly.
    createInstance(&vk_instance);
    
    // 3. Create the window surface
    createSurface(window.glfwWindow, vk_instance, &vk_surface);
    
    mainLoop(window.glfwWindow);
    
    // 4. Cleanup Vulkan and GLFW resources
    cleanup(window.glfwWindow, vk_instance, vk_surface); // **Updated call**

    return 0;
}

// --- Helper Function for Instance Creation ---
void createInstance(VkInstance *instance) {
    // 1. Specify application info (Correct, no change)
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Hello World";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // 2. Specify instance creation info
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // 3. **CRITICAL FIX AREA** Get extensions required by GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    
    // First call to get the count and the list
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    if (glfwExtensionCount == 0 || glfwExtensions == NULL) {
        // This is a common point of failure if Vulkan is not installed
        // or a needed library (like the Vulkan loader) isn't found.
        fprintf(stderr, "Failed to get required GLFW instance extensions! Check Vulkan SDK/Drivers.\n");
        exit(EXIT_FAILURE);
    }

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    
    printf("Enabling %u Vulkan instance extensions required by GLFW.\n", glfwExtensionCount);

    // 4. Create the instance
    VkResult result = vkCreateInstance(&createInfo, NULL, instance);
    if (result != VK_SUCCESS) {
        // Now you'll get a better error code if the extension isn't present for a different reason
        fprintf(stderr, "Failed to create Vulkan instance! VkResult: %d\n", result);
        exit(EXIT_FAILURE);
    }
    printf("Vulkan Instance created successfully.\n");
}

// --- Helper Function for Surface Creation ---
void createSurface(GLFWwindow* window, VkInstance pvkinstance, VkSurfaceKHR* surface) {
    // GLFW has a built-in function to create a surface from the window
    int retval = glfwCreateWindowSurface(pvkinstance, window, NULL, surface);
    if (retval != VK_SUCCESS) {
        fprintf(stderr, "Failed to create window surface!\nReason: %d\n", retval);
        exit(EXIT_FAILURE);
    }

    printf("Vulkan Window Surface created successfully.\n");
}

/**
 * @brief The main loop that keeps the window open.
 * @param window The GLFWwindow pointer.
 */
void mainLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        // Process all pending events like window closing, key presses, etc.
        glfwPollEvents();

        // **NOTE:** Since we haven't set up a Vulkan rendering pipeline (Instance, 
        // Swapchain, Render Pass, etc.) and aren't clearing the screen, 
        // the window will appear **blank** or with residual desktop content, 
        // which fulfills the requirement of this basic example.
    }
}

/**
 * @brief Cleans up Vulkan and GLFW resources.
 * @param window The GLFWwindow pointer.
 * @param instance The VkInstance to destroy.
 * @param surface The VkSurfaceKHR to destroy.
 */
void cleanup(GLFWwindow* window, VkInstance instance, VkSurfaceKHR surface) {
    // 1. Destroy the Vulkan surface
    if (surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(instance, surface, NULL);
        printf("Vulkan Window Surface destroyed.\n");
    }

    // 2. Destroy the Vulkan instance
    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, NULL);
        printf("Vulkan Instance destroyed.\n");
    }

    // 3. Destroy the GLFW window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    printf("Program terminated successfully.\n");
}