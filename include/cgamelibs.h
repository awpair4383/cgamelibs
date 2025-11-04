#include <vulkan/vulkan_core.h>

#include "GLFW/glfw3.h"

/**
 * Queries and allocates memory for Vulkan physical devices.
 * The caller is responsible for freeing the memory allocated to *ppDevices.
 *
 * @param instance The active Vulkan instance.
 * @param pPhyDevCt A pointer to an unsigned integer to store the device count.
 * @param ppDevices A pointer to a VkPhysicalDevice* to store the dynamically allocated array.
 */
void query_devices(VkInstance instance, unsigned *pPhyDevCt, VkPhysicalDevice **ppDevices);

/**
 * @struct Window
 * @brief A structure representing the main game window.
 *
 * This struct acts as a wrapper around the third-party GLFW window handle,
 * providing a clean, application-specific type for the window object.
 * This practice facilitates abstraction and makes it easier to add application-specific 
 * state (like window size or Vulkan surface handle) later without changing 
 * the window's core type throughout the program.
 */
typedef struct {
    /**
     * @var glfwWindow
     * @brief The raw handle to the GLFW window object.
     * * This pointer is managed by the GLFW library and is required for all
     * window-related operations, such as handling input and managing the context.
     */
    GLFWwindow *glfwWindow;
} Window;

/**
 * @brief Initializes GLFW and creates the window.
 * @param window A pointer to the Window to be initialized.
 */
void init_window(Window* window, int wPx, int hPx);