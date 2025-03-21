#include "fib_heap.h"

#include <assert.h>
#include <stdlib.h>

/**
 * @brief Initializes a new fibonacci heap
 */
fib_heap *fib_heap_create() {
    fib_heap *new_heap = malloc(sizeof(fib_heap));
    assert(new_heap != NULL);
    new_heap->min = NULL;

    ntree_node_list root_list = new_heap->root_list;
    root_list.items = NULL;
    root_list.count = 0;
    root_list.capacity = 0;

    return new_heap;
}

/**
 * @brief Inserts an element into the heap
 */
void fib_heap_insert(fib_heap *fheap, int n) {
    ntree_node *new_node = ntree_create_node(n);
    da_append(fheap->root_list, new_node);

    if (fheap->min == NULL || n <= fheap->min->data) {
        fheap->min = new_node;
    }
}

/**
 * @brief Returns the current minimum element from the heap (but does not remove
 * it)
 */
int fib_heap_peek(fib_heap *fheap) {
    return 0;  // TODO: stub
}

/**
 * @brief Returns the current minimum element from the heap and removes it
 */
int fib_heap_pop(fib_heap *fheap) {
    return 0;  // TODO: stub
}
