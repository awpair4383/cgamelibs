#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h> /* malloc, free */
#include <string.h>


/*  Generic vector macro
 *
 *  Usage:
 *      DEF_VECTOR(int, IntVec)
 *
 *  Generates:
 *      typedef struct { int *data; size_t capacity; size_t count; } IntVec;
 *      void IntVec_init(IntVec *vec, size_t initial_capacity);
 *      void IntVec_deinit(IntVec *vec);
 *      void IntVec_realloc(IntVec *vec, size_t new_capacity);
 *      void IntVec_push_back(IntVec *vec, int value);
 *      int  IntVec_pop_back(IntVec *vec, int *out);
 */
#define DEF_VECTOR(ELEM_T, VEC_T)                                              \
                                                                               \
	/* vector struct */                                                        \
	typedef struct {                                                           \
		ELEM_T *data;                                                          \
		size_t	capacity;                                                      \
		size_t	count;                                                         \
	} VEC_T;                                                                   \
                                                                               \
	/* initialise */                                                           \
	static inline void VEC_T##_init(VEC_T *vec, size_t initial_capacity) {     \
		if (initial_capacity == 0) {                                           \
			vec->data = NULL;                                                  \
			vec->capacity = 0;                                                 \
			vec->count = 0;                                                    \
			return;                                                            \
		}                                                                      \
		vec->data = (ELEM_T *) malloc(initial_capacity * sizeof(ELEM_T));      \
		if (!vec->data) {                                                      \
			vec->capacity = vec->count = 0;                                    \
			return;                                                            \
		}                                                                      \
		vec->capacity = initial_capacity;                                      \
		vec->count = 0;                                                        \
		memset(vec->data, 0, initial_capacity * sizeof(ELEM_T));               \
	}                                                                          \
                                                                               \
	/* de‑initialise */                                                        \
	static inline void VEC_T##_deinit(VEC_T *vec) {                            \
		if (vec->data) {                                                       \
			free(vec->data);                                                   \
			vec->data = NULL;                                                  \
		}                                                                      \
		vec->capacity = vec->count = 0;                                        \
	}                                                                          \
                                                                               \
	/* reallocate */                                                           \
	static inline void VEC_T##_realloc(VEC_T *vec, size_t new_capacity) {      \
		if (new_capacity == 0) {                                               \
			VEC_T##_deinit(vec);                                               \
			return;                                                            \
		}                                                                      \
		ELEM_T *new_data = (ELEM_T *) malloc(new_capacity * sizeof(ELEM_T));   \
		if (!new_data) return;                                                 \
		size_t copy_cnt =                                                      \
			(new_capacity < vec->count) ? new_capacity : vec->count;           \
		if (vec->data) {                                                       \
			memcpy(new_data, vec->data, copy_cnt * sizeof(ELEM_T));            \
			free(vec->data);                                                   \
		}                                                                      \
		memset(new_data + copy_cnt, 0,                                         \
			   (new_capacity - copy_cnt) * sizeof(ELEM_T));                    \
		vec->data = new_data;                                                  \
		vec->capacity = new_capacity;                                          \
		if (vec->count > new_capacity) vec->count = new_capacity;              \
	}                                                                          \
                                                                               \
	/* push_back – append a value, growing if necessary */                     \
	static inline void VEC_T##_push_back(VEC_T *vec, ELEM_T value) {           \
		if (vec->count == vec->capacity) {                                     \
			size_t new_cap = (vec->capacity == 0) ? 1 : vec->capacity * 2;     \
			VEC_T##_realloc(vec, new_cap);                                     \
		}                                                                      \
		vec->data[vec->count++] = value;                                       \
	}                                                                          \
                                                                               \
	/* pop_back – remove last element; optionally retrieve it */               \
	static inline int VEC_T##_pop_back(VEC_T *vec, ELEM_T *out) {              \
		if (vec->count == 0) return 0; /* nothing to pop */                    \
		vec->count--;                                                          \
		if (out) *out = vec->data[vec->count];                                 \
		/* optional shrink when usage drops below 1/4 of capacity */           \
		if (vec->capacity > 1 && vec->count < vec->capacity / 4) {             \
			size_t new_cap = vec->capacity / 2;                                \
			if (new_cap < vec->count) new_cap = vec->count;                    \
			VEC_T##_realloc(vec, new_cap);                                     \
		}                                                                      \
		return 1;                                                              \
	}

#endif /* VECTOR_H */