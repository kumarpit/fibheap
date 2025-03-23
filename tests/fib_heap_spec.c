#include <assert.h>
#include <criterion/criterion.h>

#include "../src/fib_heap.h"
#include "../src/utils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Test helpers
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Gets the node in the heap at the given index and returns its data cast
 * as an int pointer and dereferenced
 */
int get_index_to_int(fib_heap *fheap, int index) {
    ntree_node *node = ((ntree_node *)da_get(fheap->root_list, index));
    assert(node != NULL);

    return to_int(node->data);
}

/**
 * @brief Gets the child of the node at the given index and returns its data
 * cast as int pointer and dereferenced
 */
int get_child_at_index_to_int(fib_heap *fheap, int index) {
    ntree_node *node = ((ntree_node *)da_get(fheap->root_list, index));
    assert(node != NULL);
    ntree_node *child = node->child;
    assert(child != NULL);

    return to_int(child->data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////

Test(FibHeap, create) {
    fib_heap *fheap = fib_heap_create(&cmp_int);

    cr_assert_eq(-1, fheap->min_index);
    cr_assert_eq(0, fib_heap_root_size(fheap));
    cr_assert_eq(&cmp_int, fheap->__comparator);
}

Test(FibHeap, insert) {
    fib_heap *fheap = fib_heap_create(&cmp_int);

    int data[3];
    for (int i = 3; i > 0; i--) {
        data[i] = i;
        fib_heap_push(fheap, &data[i]);
    }

    cr_assert_eq(1, get_index_to_int(fheap, fheap->min_index));
    cr_assert_eq(3, fib_heap_root_size(fheap));
}

Test(FibHeap, peek) {
    fib_heap *fheap = fib_heap_create(&cmp_int);

    int data[3];
    for (int i = 3; i > 0; i--) {
        data[i] = i;
        fib_heap_push(fheap, &data[i]);
    }

    cr_assert_eq(1, to_int(fib_heap_peek(fheap)));
}

Test(FibHeap, pop) {
    fib_heap *fheap = fib_heap_create(&cmp_int);

    int data[3];
    for (int i = 3; i > 0; i--) {
        data[i] = i;
        fib_heap_push(fheap, &data[i]);
    }

    // Root list: 3  2  1
    cr_assert_eq(3, fib_heap_root_size(fheap));

    cr_assert_eq(1, to_int(fib_heap_pop(fheap)));
    cr_assert_eq(1, fib_heap_root_size(fheap));
    cr_assert_eq(2, to_int(fib_heap_peek(fheap)));
    cr_assert_eq(3, get_child_at_index_to_int(fheap, fheap->min_index));

    // Root list: 2-3
    cr_assert_eq(2, to_int(fib_heap_pop(fheap)));
    cr_assert_eq(1, fib_heap_root_size(fheap));

    // Root list: 3
    cr_assert_eq(3, to_int(fib_heap_peek(fheap)));
    cr_assert_eq(3, to_int(fib_heap_pop(fheap)));
    cr_assert_eq(0, fib_heap_root_size(fheap));
}

Test(FibHeap, pop_stress_test) {
    fib_heap *fheap = fib_heap_create(&cmp_int);

    int data[10000];
    for (int i = 10000; i > 0; i--) {
        data[i] = i;
        fib_heap_push(fheap, &data[i]);
    }

    for (int i = 1; i <= 10000; i++) {
        cr_assert_eq(i, to_int(fib_heap_pop(fheap)));
    }
}

Test(FibHeap, merge) {
    fib_heap *fheap1 = fib_heap_create(&cmp_int);
    int data1[3];
    for (int i = 0; i < 3; i++) {
        data1[i] = i;
        fib_heap_push(fheap1, &data1[i]);
    }

    fib_heap *fheap2 = fib_heap_create(&cmp_int);
    int data2[3];
    for (int i = 3; i < 6; i++) {
        data2[i - 3] = i;
        fib_heap_push(fheap2, &data2[i - 3]);
    }

    fib_heap_merge(fheap2, fheap1);

    cr_assert_eq(6, fib_heap_root_size(fheap2));
    cr_assert_eq(0, to_int(fib_heap_peek(fheap2)));
}

Test(FibHeap, decrease_key) {
    fib_heap *fheap = fib_heap_create(&cmp_int);

    ntree_node *nodes[3];
    int data[3];
    for (int i = -1; i < 2; i++) {
        data[i + 1] = i * 2;
        nodes[i + 1] = fib_heap_push(fheap, &data[i + 1]);
    }

    fib_heap_pop(fheap);

    int new_key = -1;
    fib_heap_decrease_key(fheap, nodes[2], &new_key);

    cr_assert_eq(2, fib_heap_root_size(fheap));
    cr_assert_eq(-1, to_int(fib_heap_peek(fheap)));
}
