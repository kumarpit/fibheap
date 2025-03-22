#include <criterion/criterion.h>

#include "../src/fib_heap.h"

Test(FibHeap, create) {
    fib_heap *fheap = fib_heap_create();

    cr_assert_eq(-1, fheap->min_index);
    cr_assert_eq(0, fheap->root_list->count);
}

Test(FibHeap, insert) {
    fib_heap *fheap = fib_heap_create();

    for (int i = 3; i > 0; i--) {
        fib_heap_insert(fheap, i);
    }

    cr_assert_eq(
        1, ((ntree_node *)da_get(fheap->root_list, fheap->min_index))->data);
    cr_assert_eq(3, fheap->root_list->count);
}

Test(FibHeap, peek) {
    fib_heap *fheap = fib_heap_create();

    for (int i = 3; i > 0; i--) {
        fib_heap_insert(fheap, i);
    }

    cr_assert_eq(1, fib_heap_peek(fheap));
}

Test(FibHeap, pop) {
    fib_heap *fheap = fib_heap_create();

    for (int i = 3; i > 0; i--) {
        fib_heap_insert(fheap, i);
    }

    // Root list >> 3  2  1
    cr_assert_eq(3, fheap->root_list->count);

    cr_assert_eq(1, fib_heap_pop(fheap));
    cr_assert_eq(1, fheap->root_list->count);
    cr_assert_eq(2, fib_heap_peek(fheap));
    cr_assert_eq(3, ((ntree_node *)da_get(fheap->root_list, fheap->min_index))
                        ->child->data);

    // Root list >> 2--3

    cr_assert_eq(2, fib_heap_pop(fheap));
    cr_assert_eq(1, fheap->root_list->count);

    // Root list >> 3

    cr_assert_eq(3, fib_heap_peek(fheap));
    cr_assert_eq(3, fib_heap_pop(fheap));
    cr_assert_eq(0, fheap->root_list->count);
}

Test(FibHeap, pop_stress_test) {
    fib_heap *fheap = fib_heap_create();

    for (int i = 10000; i > 0; i--) {
        fib_heap_insert(fheap, i);
    }

    for (int i = 1; i <= 10000; i++) {
        cr_assert_eq(i, fib_heap_pop(fheap));
    }
}

Test(FibHeap, merge) {
    fib_heap *fheap1 = fib_heap_create();
    for (int i = 0; i < 3; i++) {
        fib_heap_insert(fheap1, i);
    }

    fib_heap *fheap2 = fib_heap_create();
    for (int i = 3; i < 6; i++) {
        fib_heap_insert(fheap2, i);
    }

    fib_heap_merge(fheap2, fheap1);

    cr_assert_eq(6, fheap2->root_list->count);
    cr_assert_eq(0, fib_heap_peek(fheap2));
}

Test(FibHeap, decrease_key) {
    fib_heap *fheap = fib_heap_create();

    ntree_node *nodes[3];
    for (int i = -1; i < 2; i++) {
        nodes[i + 1] = fib_heap_insert(fheap, i * 2);
    }

    fib_heap_pop(fheap);
    fib_heap_decrease_key(fheap, nodes[2], -1);

    cr_assert_eq(2, fheap->root_list->count);
    cr_assert_eq(-1, fib_heap_peek(fheap));
}
