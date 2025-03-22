#include "fib_heap.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#include "darray.h"
#include "debug.h"
#include "ntree.h"

// Forward declarations (internal methods)
void __compact(fib_heap *);
ntree_node *__get_min_node(fib_heap *);
ntree_node *__get_node(fib_heap *, size_t index);

/**
 * @brief Initializes a new fibonacci heap
 */
fib_heap *fib_heap_create() {
    fib_heap *new_heap = malloc(sizeof(fib_heap));
    assert(new_heap != NULL);
    new_heap->min_index = -1;
    new_heap->root_list = da_create();

    return new_heap;
}

/**
 * @brief Inserts an element into the heap
 */
void fib_heap_insert(fib_heap *fheap, int n) {
    ntree_node *new_node = ntree_create_node(n);
    da_append(fheap->root_list, new_node);

    if (fheap->min_index == -1 || n <= fib_heap_peek(fheap)) {
        fheap->min_index = fheap->root_list->count - 1;
    }
}

/**
 * @brief Returns the current minimum element from the heap (but does not remove
 * it)
 */
int fib_heap_peek(fib_heap *fheap) { return __get_min_node(fheap)->data; }

/**
 * @brief Returns the current minimum element from the heap and removes it
 */
int fib_heap_pop(fib_heap *fheap) {
    assert(fheap->min_index != -1);
    int min_key = fib_heap_peek(fheap);

    debug_printf("starting pop: count in root_list -> %zu",
                 fheap->root_list->count);

    // Add all children of the minimum root tree as top-level trees in the root
    // list
    ntree_node *child = __get_min_node(fheap)->child;
    while (child) {
        da_append(fheap->root_list, child);
        child = child->sibling;
    }

    da_remove(fheap->root_list, fheap->min_index);
    debug_printf("count before compaction: %zu", fheap->root_list->count);

    if (fheap->root_list->count > 1) {
        __compact(fheap);
    } else {
        fheap->min_index = da_is_empty(fheap->root_list) ? -1 : 1;
        if (!(da_is_empty(fheap->root_list))) {  // fheap->root_list->count == 1
            ntree_node *current;
            da_for_each(fheap->root_list, current) {
                if (current != NULL) {  // find the one and only non-null
                                        // element in the root list
                    fheap->min_index = _i;
                    break;
                }
            }
        } else {  // fheap->root_list->count == 0
            fheap->min_index = -1;
        }
    }

    debug_printf("new min_index: %d", fheap->min_index);
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
    int new_min_index = -1;

    ntree_node *current;
    da_for_each(fheap->root_list, current) {  // index is available as _i
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
        if (new_min_index == -1 ||
            current_key < __get_node(fheap, new_min_index)->data) {
            new_min_index = _i;
        }
    }

    da_destroy(fheap->root_list, false);
    fheap->root_list = da_create();

    for (int i = 0; i < FIB_HEAP_MAX_DEGREE + 1; i++) {
        if (degrees_list[i] == NULL) {
            if (i < new_min_index) {
                new_min_index--;  // need to account for the fewer elements we
                                  // are adding to the new root list
            }
            continue;
        }
        da_append(fheap->root_list, degrees_list[i]);
    }

    debug_printf("ending pop: new count in root_list -> %zu",
                 fheap->root_list->count);

    fheap->min_index = new_min_index;
}

ntree_node *__get_min_node(fib_heap *fheap) {
    assert(fheap->min_index > -1);
    return __get_node(fheap, fheap->min_index);
}

ntree_node *__get_node(fib_heap *fheap, size_t index) {
    return (ntree_node *)da_get(fheap->root_list, index);
}
