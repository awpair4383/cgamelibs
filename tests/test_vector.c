/* test_intvecvec_manual.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector/vector.h"

/* ------------------------------------------------------------------ */
/* 1️⃣  Define the inner and outer vector types                         */
/* ------------------------------------------------------------------ */
DEF_VECTOR(int,      IntVec);      /* already used in the example */
DEF_VECTOR(IntVec,  IntVecVec);   /* vector of IntVec */

/* ------------------------------------------------------------------ */
/* 2️⃣  Helper to print a single IntVec (same as in the original code)*/
/* ------------------------------------------------------------------ */
static void print_intvec(const IntVec *v) {
    printf("IntVec { cap=%zu, cnt=%zu, data=[", v->capacity, v->count);
    for (size_t i = 0; i < v->capacity; ++i) {
        printf("%d", v->data[i]);
        if (i + 1 < v->capacity) printf(", ");
    }
    printf("] }\n");
}

/* ------------------------------------------------------------------ */
/* 3️⃣  Helper to print the whole IntVecVec                              */
/* ------------------------------------------------------------------ */
static void print_intvecvec(const IntVecVec *vv) {
    printf("IntVecVec { cap=%zu, cnt=%zu }\n", vv->capacity, vv->count);
    for (size_t i = 0; i < vv->count; ++i) {
        printf("  [%zu] ", i);
        print_intvec(&vv->data[i]);
    }
}

/* ------------------------------------------------------------------ */
/* 4️⃣  Test entry point                                                 */
/* ------------------------------------------------------------------ */
int main(void) {
    IntVecVec outer;

    /* ---- initialise outer container (capacity 2) ----------------- */
    init_IntVecVec(&outer, 2);
    assert(outer.capacity == 2);
    assert(outer.count    == 0);
    printf("\n=== After init outer ===\n");
    print_intvecvec(&outer);

    /* ---- manually add first inner vector --------------------------- */
    /* allocate the inner vector */
    init_IntVec(&outer.data[0], 3);          /* capacity 3 */
    outer.data[0].data[0] = 1;
    outer.data[0].data[1] = 2;
    outer.data[0].data[2] = 3;
    outer.data[0].count = 3;

    /* update outer count */
    outer.count = 1;
    printf("\n=== After inserting first inner vector ===\n");
    print_intvecvec(&outer);

    /* ---- manually add second inner vector -------------------------- */
    init_IntVec(&outer.data[1], 2);          /* capacity 2 */
    outer.data[1].data[0] = 10;
    outer.data[1].data[1] = 20;
    outer.data[1].count = 2;

    outer.count = 2;
    printf("\n=== After inserting second inner vector ===\n");
    print_intvecvec(&outer);

    /* ---- mutate an element inside the first inner vector ---------- */
    outer.data[0].data[1] = 42;   /* change 2 → 42 */
    assert(outer.data[0].data[1] == 42);
    printf("\n=== After mutating outer[0][1] ===\n");
    print_intvecvec(&outer);

    /* ---- grow outer container to capacity 4 ----------------------- */
    realloc_IntVecVec(&outer, 4);
    assert(outer.capacity == 4);
    printf("\n=== After realloc outer to capacity 4 ===\n");
    print_intvecvec(&outer);

    /* ---- shrink outer container to capacity 1 (excess elements are freed) */
    /* first clean up the elements that will be discarded */
    deinit_IntVec(&outer.data[1]);   /* element at index 1 */
    deinit_IntVec(&outer.data[2]);   /* index 2 is unused but safe to call */
    deinit_IntVec(&outer.data[3]);   /* same for index 3 */

    realloc_IntVecVec(&outer, 1);
    assert(outer.capacity == 1);
    assert(outer.count    == 1);   /* count trimmed to new capacity */
    printf("\n=== After realloc outer to capacity 1 ===\n");
    print_intvecvec(&outer);

    /* ---- final clean‑up: deinitialise remaining inner vector then outer ---- */
    deinit_IntVec(&outer.data[0]);
    deinit_IntVecVec(&outer);
    assert(outer.capacity == 0);
    assert(outer.count    == 0);
    assert(outer.data     == NULL);
    printf("\n=== After full deinitialisation ===\n");
    printf("outer: capacity=%zu, count=%zu, data=%p\n",
           outer.capacity, outer.count, (void *)outer.data);

    return 0;
}
