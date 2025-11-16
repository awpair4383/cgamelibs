#ifndef LINKED_LIST_SINGLE_H
#define LINKED_LIST_SINGLE_H

#include "stdbool.h"

#ifdef DEBUG
#define DEBUG_ASSERT(expr)                                                     \
	do {                                                                       \
		assert(expr);                                                          \
	} while (0)
#else
#define DEBUG_ASSERT(expr) ((void) 0)
#endif

#define DEF_LINKED_LIST_SINGLE(ELEM_T, NODE_T)                                 \
                                                                               \
	typedef struct NODE_T {                                                    \
		ELEM_T		   data;                                                   \
		struct NODE_T *pnext;                                                  \
	} NODE_T;                                                                  \
                                                                               \
	static void NODE_T##_insert(NODE_T *self, NODE_T *node) {                  \
		DEBUG_ASSERT(self != NULL && node != NULL);                            \
		node->pnext = self->pnext;                                             \
		self->pnext = node;                                                    \
	}                                                                          \
                                                                               \
	static void NODE_T##_init(NODE_T *self, ELEM_T data) {                     \
		DEBUG_ASSERT(self != NULL);                                            \
		self->data = data;                                                     \
		self->pnext = NULL;                                                    \
	}                                                                          \
                                                                               \
	static NODE_T *NODE_T##_remove_next(NODE_T *self) {                        \
		DEBUG_ASSERT(self != NULL);                                            \
		NODE_T *temp = self->pnext;                                            \
		if (temp != NULL) {                                                    \
			self->pnext = temp->pnext;                                         \
		}                                                                      \
		return temp;                                                           \
	}                                                                          \
                                                                               \
	static void NODE_T##_delete_next(NODE_T *self) {                           \
		DEBUG_ASSERT(self != NULL);                                            \
		NODE_T *temp = self->pnext;                                            \
		if (temp != NULL) {                                                    \
			self->pnext = temp->pnext;                                         \
			free(temp);                                                        \
		}                                                                      \
	}                                                                          \
                                                                               \
	static bool NODE_T##_has_next(NODE_T *self) {                              \
		DEBUG_ASSERT(SELF != NULL);                                            \
		return self->pnext != NULL;                                            \
	}

#endif