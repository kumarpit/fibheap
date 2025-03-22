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

    cr_assert_eq(3, fib_heap_pop(fheap));
    cr_assert_eq(0, fheap->root_list->count);
}
