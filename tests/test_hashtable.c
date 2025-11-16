#include "hashtable/hashtable.h"
#include <assert.h>
#include <stdlib.h>


// Structure definition for the test data type
struct test_t {
  int a; // First integer
  int b; // Second integer
};

// Function to test basic operations of the hash table, including insertion and
// searching for elements. This function asserts that elements can be
// successfully added and retrieved, and verifies the element count.
void test_hashtable_basic_operations() {
  // Allocate memory for the hash table and initialize it with 4 buckets
  HtTable *map = malloc(sizeof(HtTable));
  assert(map != NULL); // Ensure successful memory allocation
  ht_init_table(map, 4);

  // Initialize test data
  struct test_t test1 = {1, 2};
  struct test_t test2 = {3, 4};

  // Insert test data into the hash table
  ht_emplace(map, "Test1", &test1);
  ht_emplace(map, "Test2", &test2);

  // Verify that the elements have been correctly inserted into the hash table
  assert(ht_search(map, "Test1") != NULL); // Assert existence of test1
  assert(ht_search(map, "Test2") != NULL); // Assert existence of test2

  // Validate that the pointers returned correspond to the inserted data
  assert(ht_search(map, "Test1") == &test1); // Verify correct pointer for test1
  assert(ht_search(map, "Test2") == &test2); // Verify correct pointer for test2

  // Assert that the number of elements in the hash table is correct
  assert(map->element_count == 2); // Expecting 2 elements in the table

  // Clean up allocated resources
  ht_deinit_table(map); // Deinitialize the hash table
  free(map);            // Free the allocated memory for the hash table
}

// Function to test handling of duplicate insertions in the hash table.
// This ensures that inserting a key multiple times doesn't increase the count
// and maintains data integrity.
void test_hashtable_duplicate_insertions() {
  // Allocate and initialize the hash table
  HtTable *map = malloc(sizeof(HtTable));
  assert(map != NULL); // Check for successful memory allocation
  ht_init_table(map, 4);

  // Initialize test data
  struct test_t test1 = {1, 2};

  // Insert the test data into the hash table
  ht_emplace_s(map, "Test1", 5, &test1);
  assert(map->element_count == 1); // Should have 1 element

  // Attempt inserting the same key again
  ht_emplace_s(map, "Test1", 5, &test1);
  assert(map->element_count == 1);           // Count should remain 1
  assert(ht_search(map, "Test1") == &test1); // Verify data consistency

  // Clean up allocated resources
  ht_deinit_table(map); // Deinitialize the hash table
  free(map);            // Free allocated memory
}

// Function to test the deletion of entries in the hash table.
// This verifies that deleted keys are not retrievable and that the count is
// updated correctly.
void test_hashtable_deletion() {
  // Allocate and set up a new hash table
  HtTable *map = malloc(sizeof(HtTable));
  assert(map != NULL); // Ensure memory allocation was successful
  ht_init_table(map, 4);

  // Initialize test data
  struct test_t test1 = {1, 2};

  // Insert the test data into the hash table
  ht_emplace_s(map, "Test1", 5, &test1);
  assert(map->element_count == 1); // There should be 1 element in the table

  // Delete the inserted entry
  ht_delete(map, "Test1");
  assert(ht_search(map, "Test1") ==
         NULL);                    // Make sure the deleted key is not found
  assert(map->element_count == 0); // The count should now be 0

  // Clean up allocated resources
  ht_deinit_table(map); // Deinitialize the hash table
  free(map);            // Free allocated memory
}

// Function that runs all the test cases for the hash table operations.
void run_tests() {
  test_hashtable_basic_operations();     // Run basic operations test
  test_hashtable_duplicate_insertions(); // Run duplicate insertions test
  test_hashtable_deletion();             // Run deletion test
}

// Entry point of the program, which executes all the test cases.
int main() {
  run_tests(); // Execute the test suite
  return 0;    // Indicate successful completion
}
