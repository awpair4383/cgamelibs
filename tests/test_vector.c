/* test_intvecvec_manual.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector/vector.h"

/* ------------------------------------------------------------------ */
/* 1️⃣  Define the inner and outer vector types                         */
/* ------------------------------------------------------------------ */
DEF_VECTOR(int,      IntVec);      /* vector of ints */
DEF_VECTOR(IntVec,  IntVecVec);   /* vector of IntVec */

/* ------------------------------------------------------------------ */
/* 2️⃣  Helper to print a single IntVec (same as before)               */
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
/* 4️⃣  Test entry point – now also exercises push_back / pop_back    */
/* ------------------------------------------------------------------ */
int main(void) {
    IntVecVec outer;

    /* ---- initialise outer container (capacity 2) ----------------- */
    IntVecVec_init(&outer, 2);
    assert(outer.capacity == 2);
    assert(outer.count    == 0);
    printf("\n=== After init outer ===\n");
    print_intvecvec(&outer);

    /* ---- push_back first inner vector ----------------------------- */
    IntVec inner1;
    IntVec_init(&inner1, 3);          /* capacity 3 */
    inner1.data[0] = 1;
    inner1.data[1] = 2;
    inner1.data[2] = 3;
    inner1.count = 3;

    IntVecVec_push_back(&outer, inner1);   /* outer now owns a copy */
    assert(outer.count == 1);
    printf("\n=== After push_back inner1 ===\n");
    print_intvecvec(&outer);

    /* ---- push_back second inner vector ---------------------------- */
    IntVec inner2;
    IntVec_init(&inner2, 2);
    inner2.data[0] = 10;
    inner2.data[1] = 20;
    inner2.count = 2;

    IntVecVec_push_back(&outer, inner2);
    assert(outer.count == 2);
    printf("\n=== After push_back inner2 ===\n");
    print_intvecvec(&outer);

    /* ---- mutate an element inside the first inner vector ---------- */
    outer.data[0].data[1] = 42;   /* change 2 → 42 */
    assert(outer.data[0].data[1] == 42);
    printf("\n=== After mutating outer[0][1] ===\n");
    print_intvecvec(&outer);

    /* ---- grow outer container to capacity 4 (automatic) ---------- */
    IntVecVec_realloc(&outer, 4);
    assert(outer.capacity == 4);
    printf("\n=== After realloc outer to capacity 4 ===\n");
    print_intvecvec(&outer);

    /* ---- pop_back – remove last inner vector ---------------------- */
    IntVec popped;
    int ok = IntVecVec_pop_back(&outer, &popped);
    assert(ok && "pop_back should succeed");
    /* verify that popped contains the second inner vector */
    assert(popped.capacity == inner2.capacity);
    assert(popped.count    == inner2.count);
    assert(popped.data[0]  == 10 && popped.data[1] == 20);
    printf("\n=== After pop_back (removed inner2) ===\n");
    print_intvecvec(&outer);
    /* clean up the popped vector */
    IntVec_deinit(&popped);

    /* ---- pop_back without retrieving the value -------------------- */
    ok = IntVecVec_pop_back(&outer, NULL);
    assert(ok && "second pop_back should succeed");
    assert(outer.count == 0);
    printf("\n=== After second pop_back (removed inner1) ===\n");
    print_intvecvec(&outer);

    /* ---- attempt pop_back on empty vector – should fail --------- */
    ok = IntVecVec_pop_back(&outer, NULL);
    assert(!ok && "pop_back on empty vector must return 0");
    printf("\n=== pop_back on empty vector correctly returned 0 ===\n");

    /* ---- final clean‑up ------------------------------------------------ */
    IntVecVec_deinit(&outer);
    assert(outer.capacity == 0);
    assert(outer.count    == 0);
    assert(outer.data     == NULL);
    printf("\n=== After full deinitialisation ===\n");
    printf("outer: capacity=%zu, count=%zu, data=%p\n",
           outer.capacity, outer.count, (void *)outer.data);

    return 0;
}