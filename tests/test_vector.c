#include <stdio.h>
#include <stdlib.h>
#include "vector/vector.h"

DEF_VECTOR(int, IntVec)

static void print_intvec(const IntVec *v) {
    printf("IntVec { capacity=%zu, count=%zu, data=[", v->capacity, v->count);
    for (size_t i = 0; i < v->capacity; ++i) {
        printf("%d", v->data[i]);
        if (i + 1 < v->capacity) printf(", ");
    }
    printf("] }\n");
}

int main(void) {
    IntVec vec;

    printf("=== Initialise with capacity 4 ===\n");
    init_IntVec(&vec, 4);
    print_intvec(&vec);

    printf("\n=== Add two elements (10, 20) ===\n");
    vec.data[0] = 10;
    vec.data[1] = 20;
    vec.count = 2;
    print_intvec(&vec);

    printf("\n=== Grow to capacity 8 ===\n");
    realloc_IntVec(&vec, 8);
    print_intvec(&vec);

    printf("\n=== Shrink to capacity 3 ===\n");
    realloc_IntVec(&vec, 3);
    print_intvec(&vec);

    printf("\n=== Deinitialise ===\n");
    deinit_IntVec(&vec);
    printf("After deinit: capacity=%zu, count=%zu, data=%p\n",
           vec.capacity, vec.count, (void *)vec.data);

    return 0;
}
