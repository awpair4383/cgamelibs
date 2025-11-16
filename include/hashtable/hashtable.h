#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stdbool.h" // bool type
#include "stddef.h"  // Standard definitions (e.g., size_t)
#include "stdlib.h"  // Memory allocation functions (malloc, free)
#include "string.h"  // String manipulation functions (strcpy)

// Memory management macros for simplified allocation and deallocation
#define htmalloc(size) malloc(size)
#define htfree(p) free(p)

// Struct definition for a node in the hash table's linked list
typedef struct HtNode {
  char *key;            // Key for the hash table entry (null-terminated string)
  void *value;          // Pointer to the value associated with the key
  struct HtNode *pnext; // Pointer to the next node for handling collisions
} HtNode;

// Struct definition for the hash table itself
typedef struct HtTable {
  HtNode **buckets; // Array of pointers to linked list heads representing hash
                    // table buckets
  unsigned bucket_count;  // Total number of buckets in the hash table
  unsigned element_count; // Current number of key-value pairs in the hash table
} HtTable;

// Function prototypes for hash table operations

/**
 * Initializes a hash table with the specified number of buckets. Allocates
 * memory for the buckets and sets the initial element count to zero.
 *
 * @param tab Pointer to the hash table to be initialized.
 * @param bucket_count Number of buckets to create in the hash table.
 */
void ht_init_table(HtTable *tab, unsigned bucket_count);

/**
 * Inserts a key-value pair into the hash table. If the key already exists, the
 * existing value will be updated.
 *
 * @param tab Pointer to the hash table.
 * @param key The key to insert (must be a null-terminated string).
 * @param value Pointer to the value associated with the key.
 * @return True if the insertion (or update) is successful, false otherwise.
 */
bool ht_emplace(HtTable *tab, char *key, void *value);

/**
 * Inserts a key-value pair into the hash table using a specified key size. This
 * is useful for non-string keys. Any previously associated value with the key
 * will be replaced.
 *
 * @param tab Pointer to the hash table.
 * @param key Pointer to the key to insert.
 * @param keylen The length in bytes of the key (excluding the null terminator).
 * @param value Pointer to the value associated with the key.
 * @return True if the insertion is successful, false otherwise.
 */
bool ht_emplace_s(HtTable *tab, void *key, size_t keylen, void *value);

/**
 * Deletes a key-value pair from the hash table.
 * If the key is not found, no action is performed, and false is returned.
 *
 * @param tab Pointer to the hash table.
 * @param key Pointer to the key to delete (must be a null-terminated string).
 * @return True if the deletion is successful, false if the key was not found.
 */
bool ht_delete(HtTable *tab, void *key);

/**
 * Searches for a value associated with a given key in the hash table.
 * If the key is not found, NULL is returned.
 *
 * @param tab Pointer to the hash table.
 * @param key Pointer to the key to search for (must be a null-terminated
 * string).
 * @return Pointer to the value associated with the key, or NULL if not found.
 */
void *ht_search(HtTable *tab, void *key);

/**
 * Searches for a value associated with a given key in the hash table.
 * This function uses a specified key length for comparison. If the key
 * is not found, NULL is returned.
 *
 * @param tab Pointer to the hash table.
 * @param key Pointer to the key to search for (should be a string).
 * @param keylen Length of the key to be compared.
 * @return Pointer to the value associated with the key, or NULL if not found.
 */
void *ht_search_s(HtTable *tab, void *key, size_t keylen);

/**
 * Deinitializes a hash table, freeing all allocated resources. This includes
 * the memory for keys, values, and the nodes in the linked lists.
 *
 * @param tab Pointer to the hash table to deinitialize.
 */
void ht_deinit_table(HtTable *tab);

/**
 * Checks if a key exists in the hash table.
 * This function returns true if the key is found, and false otherwise.
 *
 * @param tab Pointer to the hash table.
 * @param key Pointer to the key to check (must be a null-terminated string).
 * @return True if the key exists in the hash table, false otherwise.
 */
bool ht_has(HtTable *tab, void *key);

#endif // HASHTABLE_H