#ifndef CGAMELIBS_H
#define CGAMELIBS_H
#include <vulkan/vulkan_core.h>

#include "GLFW/glfw3.h"

/**
 * @struct Window
 * @brief A structure representing the main game window.
 *
 * This struct acts as a wrapper around the third-party GLFW window handle,
 * providing a clean, application-specific type for the window object.
 * This practice facilitates abstraction and makes it easier to incorporate
 * application-specific state (like window size or Vulkan surface handle) later
 * without changing the core type throughout the program.
 */
typedef struct {
  /**
   * @var glfwWindow
   * @brief The raw handle to the GLFW window object.
   *
   * This pointer is managed by the GLFW library and is required for all
   * window-related operations, such as handling input and managing
   * the window's graphics context.
   */
  GLFWwindow *glfwWindow;

  /**
   * @var vkInstance
   * @brief The Vulkan instance associated with this window.
   *
   * This instance is used to interface with Vulkan and is typically created
   * during the setup of the Vulkan application.
   */
  VkInstance vkInstance;

  /**
   * @var vkSurfaceKHR
   * @brief The Vulkan surface handle for this window.
   *
   * This handle represents the surface on which Vulkan can render images
   * to be displayed in the window. It is created based on the GLFW window
   * and is essential for Vulkan's rendering pipeline.
   */
  VkSurfaceKHR vkSurfaceKHR;

  /**
   * @brief Array of handles to physical devices available to the Vulkan
   * application.
   *
   * This member stores pointers to VkPhysicalDevice handles, allowing
   * the application to manage and interact with multiple physical devices
   * as needed. The array can be used to query device properties,
   * capabilities, and to select the most suitable device for rendering.
   *
   * @note Ensure to manage the memory of this array appropriately,
   * especially when dealing with multiple devices.
   */
  VkPhysicalDevice *vkPhysicalDevs;

  /**
   * @brief Number of physical devices available.
   *
   * This member holds the count of the physical devices stored in
   * the vkPhysicalDevs array. It is essential for iterating over the
   * array and managing device selection or queries.
   */
  unsigned vkPhysicalDevCount;
} Window;

/**
 * Queries and allocates memory for Vulkan physical devices.
 * The caller is responsible for freeing the memory allocated to *ppDevices.
 *
 * @param window The game window
 */
void init_devices(Window *const window);

/**
 * @brief Initializes GLFW and creates the window.
 * @param window A pointer to the Window to be initialized.
 */
void init_window(Window *const window, const uint16_t wPx, const uint16_t hPx); // should handle a maximum of 65535 X 65535, consider making these floats for subpixel precision/rendering.

/**
 * @brief Creates a Vulkan surface associated with the specified window.
 *
 * This function initializes a Vulkan surface for rendering images, which
 * is linked to the GLFW window provided through the `Window` struct.
 * The function retrieves the necessary information from the struct,
 * creating a surface that Vulkan can use for rendering.
 *
 * @param window Pointer to a `Window` struct containing the GLFW
 * window handle and Vulkan instance for which the surface is created.
 */
void init_surface(Window *const window);

/**
 * @brief Initializes the Vulkan instance for the specified window.
 *
 * This function sets up the Vulkan instance needed for rendering in the
 * provided `Window` struct. It configures necessary parameters and creates
 * the Vulkan instance, linking it to the window.
 *
 * @param win Pointer to a `Window` struct where the Vulkan instance
 *            will be initialized. This instance is essential for all Vulkan
 *            operations related to this window.
 */
void init_vkinstance(Window *const win);

/**
 * @brief Frees Vulkan physical device handles previously allocated by init_devices.
 *
 * Frees the memory pointed to by window->vkPhysicalDevs and resets the count.
 * Safe to call multiple times; silently returns if window is NULL or vkPhysicalDevs is NULL.
 *
 * Example usage:
 * @code
 * init_devices(&window);
 * // ... use devices ...
 * deinit_devices(&window);
 * @endcode
 *
 * @param[in,out] window Pointer to the Window structure that owns the device array.
 */
void deinit_devices(Window *const window);

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
void deinit_surface(Window *const window);

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
void deinit_window(Window *const window);

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
void deinit_vkinstance(Window *const win);
#endif