#include "fib_heap.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "darray.h"
#include "ntree.h"

// Forward declarations (internal methods)
void __compact(fib_heap *);

/**
 * @brief Initializes a new fibonacci heap
 */
fib_heap *fib_heap_create() {
    fib_heap *new_heap = malloc(sizeof(fib_heap));
    assert(new_heap != NULL);
    new_heap->min = NULL;
    new_heap->root_list = da_create();

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
int fib_heap_peek(fib_heap *fheap) { return fheap->min->data; }

/**
 * @brief Returns the current minimum element from the heap and removes it
 */
int fib_heap_pop(fib_heap *fheap) {
    assert(fheap->min != NULL);
    int min_key = fheap->min->data;

    // Add all children of the minimum root tree as top-level trees in the root
    // list
    ntree_node *child = fheap->min->child;
    while (child) {
        da_append(fheap->root_list, child);
        child = child->sibling;
    }
    // TODO: keep track of free items in the items list
    free(fheap->min);
    fheap->min = NULL;
    fheap->root_list->count--;

    if (!(da_is_empty(fheap->root_list))) {
        __compact(fheap);
    }

    return min_key;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Internal method definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reduces the size of the root list by linking together trees of the
 * same degree
 */
void __compact(fib_heap *fheap) {
    ntree_node *degrees_list[FIB_HEAP_MAX_DEGREE + 1] = {NULL};
    ntree_node *new_min = NULL;

    ntree_node *current;
    da_for_each(fheap->root_list, current) {
        if (current == NULL) continue;
        int degree = current->degree;

        // Keep merging trees of same degrees - we should end up with at most
        // one tree per degree
        ntree_node *existing = degrees_list[degree];
        while (existing != NULL) {
            int current_key = current->data;
            int exisiting_key = existing->data;
            if (exisiting_key < current_key) {
                ntree_insert_child(current, existing);
                current = existing;
            } else {
                ntree_insert_child(existing, current);
            }
            degrees_list[degree] = NULL;
            degree = current->degree;
            assert(degree <= FIB_HEAP_MAX_DEGREE);
            existing = degrees_list[degree];
        }

        degrees_list[degree] = current;

        int current_key = current->data;
        if (new_min == NULL || current_key < new_min->data) {
            new_min = current;
        }
    }

    fheap->min = new_min;
    da_destroy(fheap->root_list, false);
    fheap->root_list = da_create();

    for (int i = 0; i < FIB_HEAP_MAX_DEGREE + 1; i++) {
        if (degrees_list[i] == NULL) continue;
        da_append(fheap->root_list, degrees_list[i]);
    }
}
