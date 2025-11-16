#include <stdio.h>
#include <stdlib.h>
#include "cgamelibs.h"

// --- Helper Function for Instance Creation ---
void init_vkinstance(Window *const win) {
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
	uint32_t	 glfwExtensionCount = 0;
	const char **glfwExtensions;

	// First call to get the count and the list
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	if (glfwExtensionCount == 0 || glfwExtensions == NULL) {
		// This is a common point of failure if Vulkan is not installed
		// or a needed library (like the Vulkan loader) isn't found.
		fprintf(stderr,
				"Failed to get required GLFW instance extensions! Check "
				"Vulkan SDK/Drivers.\n");
		exit(EXIT_FAILURE);
	}

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	printf("Enabling %u Vulkan instance extensions required by GLFW.\n",
		   glfwExtensionCount);

	// 4. Create the instance
	VkResult result = vkCreateInstance(&createInfo, NULL, &win->vkInstance);
	if (result != VK_SUCCESS) {
		// Now you'll get a better error code if the extension isn't present for
		// a different reason
		fprintf(stderr, "Failed to create Vulkan instance! VkResult: %d\n",
				result);
		exit(EXIT_FAILURE);
	}
	printf("Vulkan Instance created successfully.\n");
}

/**
 * @brief Cleans up and destroys the Vulkan instance.
 *
 * This function uses vkDestroyInstance to release all resources associated
 * with the Vulkan instance handle stored in the `Window` struct. This is
 * typically the *last* Vulkan-related cleanup step before application exit.
 *
 * @param window Pointer to the `Window` struct containing the Vulkan
 * instance (`vkInstance`) to be destroyed.
 */
void deinit_vkinstance(Window *const win) {
	// The vkDestroyInstance function destroys the specified VkInstance.
	// All child objects (like the surface) must have been destroyed
	// before this function is called.
	vkDestroyInstance(win->vkInstance, NULL);

	// Optional: Set the handle to VK_NULL_HANDLE after destruction
	// to prevent accidental use (good practice).
	win->vkInstance = VK_NULL_HANDLE;
	printf("Vulkan Instance destroyed successfully.\n");
}