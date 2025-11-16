#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "cgamelibs.h"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Function declarations
void mainLoop(GLFWwindow *window);
void cleanup(GLFWwindow *window, VkInstance instance, VkSurfaceKHR surface);
// void create_instance(VkInstance *instance);

int main() {
	Window window;

	VkInstance	 vk_instance = VK_NULL_HANDLE; // Initialize to null
	VkSurfaceKHR vk_surface = VK_NULL_HANDLE;  // Initialize to null

	// 1. Initialize GLFW and create the window
	// This calls glfwInit(), which must happen before querying extensions.
	init_window(&window, 800, 600);

	// 2. Create the Vulkan instance
	// Now glfwGetRequiredInstanceExtensions will work correctly.
	init_vkinstance(&window);

	init_devices(&window);

	// 3. Create the window surface
	init_surface(&window);

	// mainLoop(window.glfwWindow);

	// 4. Cleanup Vulkan and GLFW resources
	deinit_surface(&window);
	deinit_vkinstance(&window);
	deinit_devices(&window);
	deinit_window(&window);

	return 0;
}

/**
 * @brief The main loop that keeps the window open.
 * @param window The GLFWwindow pointer.
 */
void mainLoop(GLFWwindow *window) {
	while (!glfwWindowShouldClose(window)) {
		// Process all pending events like window closing, key presses, etc.
		glfwPollEvents();

		// **NOTE:** Since we haven't set up a Vulkan rendering pipeline
		// (Instance, Swapchain, Render Pass, etc.) and aren't clearing the
		// screen, the window will appear **blank** or with residual desktop
		// content, which fulfills the requirement of this basic example.
	}

	glfwTerminate();
}