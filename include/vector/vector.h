#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <string.h>

/*  Generic vector macro
 *
 *  Usage:
 *      DEFINE_VECTOR(int, IntVec)
 *
 *  Expands to:
 *      typedef int ELEM_T;
 *      typedef struct { ELEM_T *data; size_t capacity; size_t count; } VEC_T;
 *      void init_VEC_T(VEC_T *vec, size_t initial_capacity);
 *      void deinit_VEC_T(VEC_T *vec);
 *      void realloc_VEC_T(VEC_T *vec, size_t new_capacity);
 */
#define DEF_VECTOR(ELEM_T, VEC_T)                                           \
                                                                               \
	/* vector struct */                                                        \
	typedef struct {                                                           \
		ELEM_T *data;                                                          \
		size_t	capacity;                                                      \
		size_t	count;                                                         \
	} VEC_T;                                                                   \
                                                                               \
	/* initialise */                                                           \
	static inline void init_##VEC_T(VEC_T *vec, size_t initial_capacity) {     \
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
	static inline void deinit_##VEC_T(VEC_T *vec) {                            \
		if (vec->data) {                                                       \
			free(vec->data);                                                   \
			vec->data = NULL;                                                  \
		}                                                                      \
		vec->capacity = vec->count = 0;                                        \
	}                                                                          \
                                                                               \
	/* reallocate */                                                           \
	static inline void realloc_##VEC_T(VEC_T *vec, size_t new_capacity) {      \
		if (new_capacity == 0) {                                               \
			deinit_##VEC_T(vec);                                               \
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
	}
    
#endif