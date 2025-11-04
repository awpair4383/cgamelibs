#include <stdio.h>
#include <stdlib.h> // Required for malloc
#include <vulkan/vulkan_core.h>

#include "cgamelibs.h"

/**
 * Queries and allocates memory for Vulkan physical devices.
 * The caller is responsible for freeing the memory allocated to *ppDevices.
 *
 * @param instance The active Vulkan instance.
 * @param pPhyDevCt A pointer to an unsigned integer to store the device count.
 * @param ppDevices A pointer to a VkPhysicalDevice* to store the dynamically allocated array.
 */
void query_devices(VkInstance instance, unsigned *pPhyDevCt, VkPhysicalDevice **ppDevices) {
    // Vulkan uses uint32_t for counts, but we'll use 'unsigned' as requested
    uint32_t count = 0;
    VkResult res;

    // Initialize output pointers to a safe state
    if (pPhyDevCt) *pPhyDevCt = 0;
    if (ppDevices) *ppDevices = NULL;

    // --- 1. Get the number of physical devices (Count phase) ---
    // Note: We use a local uint32_t 'count' to ensure type compatibility with vkEnumeratePhysicalDevices
    res = vkEnumeratePhysicalDevices(instance, &count, NULL);

    if (res != VK_SUCCESS) {
        fprintf(stderr, "Error: Failed to query physical device count (VkResult: %d).\n", res);
        return;
    }

    if (count == 0) {
        fprintf(stderr, "Warning: No physical devices with Vulkan support found.\n");
        return;
    }

    // --- 2. Dynamic Memory Allocation ---
    if (ppDevices == NULL) {
        fprintf(stderr, "Error: ppDevices pointer is NULL, cannot allocate memory.\n");
        return;
    }

    // Allocate memory on the heap (The fix for the stack allocation error)
    *ppDevices = (VkPhysicalDevice *)malloc(count * sizeof(VkPhysicalDevice));
    if (*ppDevices == NULL) {
        fprintf(stderr, "Fatal Error: Failed to allocate memory for %u physical devices.\n", count);
        return;
    }

    // --- 3. Get the physical devices (Population phase) ---
    // Pass the allocated array pointer to retrieve the device handles
    res = vkEnumeratePhysicalDevices(instance, &count, *ppDevices);

    if (res != VK_SUCCESS && res != VK_INCOMPLETE) {
        fprintf(stderr, "Error: Failed to enumerate physical devices (VkResult: %d).\n", res);
        // Clean up allocated memory on failure
        free(*ppDevices);
        *ppDevices = NULL;
        return;
    }

    // --- 4. Success: Set the final count and devices for the caller ---
    if (pPhyDevCt) {
        *pPhyDevCt = (unsigned)count;
    }

    printf("Successfully found and retrieved %u physical device(s).\n", count);
}