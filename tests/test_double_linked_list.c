#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list/double.h"

DEF_LINKED_LIST_DOUBLE(int, IntNode);

void test_init() {
	IntNode node;
	IntNode_init(&node, 10);
	assert(node.data == 10);
	assert(node.pnext == NULL);
	assert(node.pprev == NULL);
	printf("Passed test_init.\n");
}

void test_insert_after() {
	IntNode head;
	IntNode_init(&head, 1);

	IntNode *newNode = malloc(sizeof(IntNode));
	IntNode_init(newNode, 2);

	IntNode_insert_after(&head, newNode);

	assert(head.pnext != NULL);
	assert(head.pnext->data == 2);
	assert(head.pnext->pprev == &head);
	assert(head.pnext->pnext == NULL);

    free(newNode);

	printf("Passed test_insert_after.\n");
}

void test_delete_next() {
	IntNode head;
	IntNode_init(&head, 1);

	IntNode secondNode;
	IntNode_init(&secondNode, 2);
	IntNode_insert_after(&head, &secondNode);

	IntNode thirdNode;
	IntNode_init(&thirdNode, 3);
	IntNode_insert_after(head.pnext,
						 &thirdNode); // Now head --> secondNode --> thirdNode

	// Initial state
	assert(head.pnext != NULL);		   // There is a second node
	assert(head.pnext->pnext != NULL); // There is a third node
	assert(head.pnext->pnext->data == 3);
	assert(head.pnext->pnext->pprev == head.pnext); // Check previous link

	// Perform deletion
	IntNode_remove_next(&secondNode); // Deletes secondNode

	// After deletion
	assert(head.pnext != NULL);	   // Head still has a next node
	assert(head.pnext->data == 2); // Now it points directly to the third node
	assert(head.pnext->pnext == NULL); // Third node's next should be NULL
	assert(head.pnext->pprev ==
		   &head); // Third node's previous should point to head

	printf("Passed test_delete_next.\n");
}

void test_has_next() {
	IntNode head;
	IntNode_init(&head, 1);
	assert(!IntNode_has_next(&head)); // Initially there should be no next node

	IntNode *newNode = malloc(sizeof(IntNode));
	IntNode_init(newNode, 2);
	IntNode_insert_after(&head, newNode);

	assert(IntNode_has_next(&head)); // Now there should be a next node

    free(newNode);

	printf("Passed test_has_next.\n");
}

int main() {
	test_init();
	test_insert_after();
	test_delete_next();
	test_has_next();

	printf("All tests passed!\n");
	return 0;
}
