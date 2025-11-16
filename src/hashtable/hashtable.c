#include "hashtable/hashtable.h"
#include "hashtable/hash.h"

DEF_HASH_FN_NULLTERM(unsigned);
DEF_HASH_FN_SIZED(unsigned);

#define hash_key(key) hash_unsigned_nullterm(key)
#define hash_key_s(key, len) hash_unsigned_sized(key, len)

void ht_init_table(HtTable *tab, unsigned bucket_count)
{
    tab->buckets = htmalloc(sizeof(HtNode *) * bucket_count);

    for (unsigned i = 0; i < bucket_count; ++i)
    {
        tab->buckets[i] = NULL;
    }

    tab->bucket_count = bucket_count;
    tab->element_count = 0;
}

void ht_deinit_table(HtTable *tab)
{
    for (unsigned int i = 0; i < tab->bucket_count; ++i)
    {
        HtNode *currNode = tab->buckets[i];
        while (currNode != NULL)
        {
            HtNode *tempNode = currNode; // Keep track of the current node to free it afterwards
            currNode = currNode->pnext;  // Move to the next node
            htfree(tempNode->key);       // Free the key
            htfree(tempNode);            // Free the current node
        }
    }

    htfree(tab->buckets);   // Free the array of buckets
    tab->buckets = NULL;    // Avoid dangling pointer
    tab->bucket_count = 0;  // Reset bucket count
    tab->element_count = 0; // Reset element count
}

bool ht_insert_s(HtTable *tab, void *key, size_t keylen, void *value)
{
    unsigned int idx = hash_key_s(key, keylen) % tab->bucket_count;

    // Create a new node.
    HtNode *new_node = htmalloc(sizeof(HtNode));
    if (!new_node)
    {
        // Handle allocation failure.
        return false;
    }

    new_node->key = htmalloc(keylen + 1);

    new_node->key[keylen] = '\0';

    // Duplicate the key
    // should be `keylen + 1` to account for the null terminator instead of just `keylen`
    strcpy_s(new_node->key, keylen + 1, key);

    new_node->value = value;

    new_node->pnext = NULL;

    // Insert into the hash table bucket.
    if (tab->buckets[idx] == NULL)
    {
        // No collision, simply insert the new node.
        tab->buckets[idx] = new_node;
    }
    else
    {
        // Handle collision: insert at the beginning of the linked list.
        new_node->pnext = tab->buckets[idx]; // Point to the current first node
        tab->buckets[idx] = new_node;        // Update the bucket to point to the new node
    }

    tab->element_count++; // Increase the count of elements.

    return true;
}

bool ht_insert(HtTable *tab, char *key, void *value)
{
    size_t len = strlen(key);
    return ht_insert_s(tab, key, len, value);
}

bool ht_delete(HtTable *tab, void *key)
{
    // Calculate the bucket index using the hash function
    unsigned int idx = hash_key(key) % tab->bucket_count;

    HtNode *prevNode = NULL;
    HtNode *currNode = tab->buckets[idx];

    while (currNode != NULL)
    {
        // Check if the current node's key matches the key to delete
        if (strcmp((const char *)currNode->key, (const char *)key) == 0)
        {
            // If the node to delete is the head of the list
            if (currNode == tab->buckets[idx])
            {
                tab->buckets[idx] = currNode->pnext; // Update head to the next node
            }
            else
            {
                // If it's a middle or last node
                prevNode->pnext = currNode->pnext; // Bypass the current node
            }
            htfree(currNode->key); // Free the key
            htfree(currNode);      // Free the node itself
            tab->element_count--;  // Decrement the element count
            return true;           // Exit the function
        }
        prevNode = currNode;        // Move to next node
        currNode = currNode->pnext; // Continue traversal
    }

    return false;
}

void *ht_search(HtTable *tab, void *key)
{
    // Getting the bucket index for the given key
    unsigned int bucketIndex = hash_key(key) % tab->bucket_count;

    // Head of the linked list present at bucket index
    HtNode *bucketHead = tab->buckets[bucketIndex];
    while (bucketHead != NULL)
    {
        // Compare the actual string values
        if (strcmp((const char *)bucketHead->key, (const char *)key) == 0)
        {
            // Key is found in the hashMap
            return bucketHead->value; // Return the associated value
        }
        bucketHead = bucketHead->pnext; // Move to the next node
    }

    return NULL; // Return NULL if the key is not found
}