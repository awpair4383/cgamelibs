#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list/single.h"

// Include the definition for your linked list here
// #define DEBUG (if needed)
// #define DEF_LINKED_LIST_SINGLE(ELEM_T, NODE_T) from the previous response

DEF_LINKED_LIST_SINGLE(int, IntNode);

void test_init() {
	IntNode node;
	IntNode_init(&node, 10);
	assert(node.data == 10);
	assert(node.pnext == NULL);
	printf("Passed test_init.\n");
}

void test_insert() {
	IntNode head;
	IntNode_init(&head, 1);

	IntNode *newNode = malloc(sizeof(IntNode));
	IntNode_init(newNode, 2);

	IntNode_insert(&head, newNode);

	assert(head.pnext != NULL);
	assert(head.pnext->data == 2);
	assert(head.pnext->pnext == NULL);

	printf("Passed test_insert.\n");
}

void test_delete_next() {
	IntNode head;
	IntNode_init(&head, 1);

	IntNode *secondNode = malloc(sizeof(IntNode));
	IntNode_init(secondNode, 2);
	IntNode_insert(&head, secondNode);

	IntNode *thirdNode = malloc(sizeof(IntNode));
	IntNode_init(thirdNode, 3);
	IntNode_insert(head.pnext,
				   thirdNode); // Now head --> secondNode --> thirdNode

	// Initial state
	assert(head.pnext != NULL);		   // There is a second node
	assert(head.pnext->pnext != NULL); // There is a third node
	assert(head.pnext->pnext->data == 3);

	// Perform deletion
	IntNode *removed = IntNode_remove_next(&head); // Deletes secondNode

	if (removed) free(removed);

	// After deletion
	assert(head.pnext != NULL);	   // Head still has a next node
	assert(head.pnext->data == 3); // Now it points directly to the third node
	assert(head.pnext->pnext == NULL); // Third node's next should be NULL

	printf("Passed test_delete_next.\n");
}

int main() {
	test_init();
	test_insert();
	test_delete_next();

	printf("All tests passed!\n");
	return 0;
}
