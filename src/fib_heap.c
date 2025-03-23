#include "fib_heap.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include "darray.h"
#include "debug.h"
#include "ntree.h"

// Forward declarations (private methods)
void __compact(fib_heap *);
void __cut(fib_heap *, ntree_node *);
ntree_node *__get_min_node(fib_heap *);
ntree_node *__get_node(fib_heap *, size_t index);
bool __is_less_than(fib_heap *, void *a, void *b);
void __dump_node(ntree_node *, int index, int level);
void __free_node(void *);

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// FibHeap interface implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes a new fibonacci heap
 */
fib_heap *fib_heap_create(cmp_func __comparator) {
    fib_heap *new_heap = malloc(sizeof(fib_heap));
    assert(new_heap != NULL);
    new_heap->min_index = -1;
    new_heap->root_list = da_create(__free_node);
    new_heap->__comparator = __comparator;

    return new_heap;
}

/**
 * @brief Returns true if the heap has no elements in it, false otherwise
 */
bool fib_heap_is_empty(fib_heap *fheap) {
    return da_is_empty(fheap->root_list);
}

/**
 * @brief Inserts an element into the heap
 */
ntree_node *fib_heap_push(fib_heap *fheap, void *data) {
    ntree_node *new_node = ntree_create_node(data);
    da_append(fheap->root_list, new_node);

    if (fheap->min_index == -1 ||
        __is_less_than(fheap, data, fib_heap_peek(fheap))) {
        fheap->min_index = fheap->root_list->count - 1;
    }

    return new_node;
}

/**
 * @brief Returns the current minimum element from the heap (but does not remove
 * it)
 */
void *fib_heap_peek(fib_heap *fheap) { return __get_min_node(fheap)->data; }

/**
 * @brief Returns the current minimum element from the heap and removes it
 */
void *fib_heap_pop(fib_heap *fheap) {
    assert(fheap->min_index != -1);
    void *min_key = fib_heap_peek(fheap);

    debug_printf("starting pop");
    debug_printf("heap state:");
    fib_heap_dump(fheap);

    // Add all children of the minimum root tree as top-level trees in the root
    // list
    ntree_node *child = __get_min_node(fheap)->child;
    while (child) {
        debug_printf("appending child");
        da_append(fheap->root_list, child);
        child = child->sibling;
    }

    debug_printf("heap state after appending children");
    fib_heap_dump(fheap);

    da_remove(fheap->root_list, fheap->min_index, true);

    if (!fib_heap_is_empty(fheap)) {
        __compact(fheap);
    } else {
        fheap->min_index = -1;
    }

    debug_printf("end of pop");
    return min_key;
}

/**
 * @brief Merges the other fibonacci heap into self
 */
void fib_heap_merge(fib_heap *self, fib_heap *other) {
    assert(self != NULL);
    assert(other != NULL);

    da_for_each(other->root_list) { da_append(self->root_list, _current); }

    void *self_min = fib_heap_peek(self);
    void *other_min = fib_heap_peek(other);

    if (__is_less_than(self, other_min, self_min)) {
        da_for_each(self->root_list) {
            if (((ntree_node *)_current)->data == other_min) {
                self->min_index = _i;
                break;
            }
        }
    }
}

/**
 * @brief Decrease the value of the given node to the `new_key` value and
 * re-organize heap to maintain heap invariant
 */
void fib_heap_decrease_key(fib_heap *fheap, ntree_node *node, void *new_key) {
    assert(node != NULL);
    assert(new_key < node->data);

    node->data = new_key;

    if (node->parent != NULL) {
        if (__is_less_than(fheap, new_key, node->parent->data)) {
            __cut(fheap, node);
        }
    }

    if (!fib_heap_is_empty(fheap)) {
        if (new_key < fib_heap_peek(fheap)) {
            da_for_each(fheap->root_list) {
                if (((ntree_node *)_current)->data == new_key) {
                    fheap->min_index = _i;
                    break;
                }
            }
        }
    }
}

/**
 * @brief Pretty-prints the state of the heap, useful for debugging relatively
 * small-sized heaps
 */
void fib_heap_dump(fib_heap *fheap) {
    debug_printf("-------------Dumping Heap----------------");
    debug_printf("Min Index: %d", fheap->min_index);
    da_for_each(fheap->root_list) {
        __dump_node((ntree_node *)_current, _i, 0);
    }
    debug_printf("-----------------------------------------");
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Private method definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Reduces the size of the root list by linking together trees of the
 * same degree
 */
void __compact(fib_heap *fheap) {
    ntree_node *degrees_list[FIB_HEAP_MAX_DEGREE + 1] = {NULL};
    void *min_key = NULL;

    ntree_node *current;
    da_for_each(fheap->root_list) {
        current = (ntree_node *)_current;
        int degree = current->degree;

        // Keep merging trees of same degrees - we should end up with at most
        // one tree per degree
        ntree_node *existing = degrees_list[degree];
        while (existing != NULL) {
            void *current_key = current->data;
            void *exisiting_key = existing->data;
            if (__is_less_than(fheap, exisiting_key, current_key)) {
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

        void *current_key = current->data;
        if (min_key == NULL || __is_less_than(fheap, current_key, min_key)) {
            min_key = current_key;
        }
    }

    da_destroy(fheap->root_list, false);
    fheap->root_list = da_create(__free_node);

    // Only add back non-null elements to the new root list. This makes up for
    // the drawbacks of my dyanmic array implementation (which leaves gaps in
    // the list in order to support removing elements at arbitrary indices)
    int relative_index = 0;
    int min_index = 0;
    for (int i = 0; i < FIB_HEAP_MAX_DEGREE + 1; i++) {
        if (degrees_list[i] == NULL) {
            continue;
        }
        da_append(fheap->root_list, degrees_list[i]);
        if (degrees_list[i]->data == min_key) {
            min_index = relative_index;
        }
        relative_index++;
    }

    fheap->min_index = min_index;
    debug_printf("heap after compaction:");
    fib_heap_dump(fheap);
}

/**
 * @brief Cuts the given node from its parent and adds it to the root list
 */
void __cut(fib_heap *fheap, ntree_node *node) {
    assert(fheap != NULL);
    assert(node != NULL);

    if (node->parent == NULL) return;

    ntree_node *parent = node->parent;
    node->marked = false;

    ntree_remove_child(node, false);
    da_append(fheap->root_list, node);

    if (!(parent->marked)) {
        parent->marked = true;
    } else {
        __cut(fheap, parent);
    }
}

/**
 * @brief Gets the ntree node containing the current minimum element
 */
ntree_node *__get_min_node(fib_heap *fheap) {
    assert(fheap->min_index > -1);
    return __get_node(fheap, fheap->min_index);
}

/**
 * @brief Wrapper function to get the ntree node at the given index in the root
 * list
 */
ntree_node *__get_node(fib_heap *fheap, size_t index) {
    return (ntree_node *)da_get(fheap->root_list, index);
}

/**
 * @brief Pretty-print helper to dump fibonacci heap state
 */
void __dump_node(ntree_node *node, int index, int level) {
    // TODO: use a custom print function here as well
    debug_printf_with_indent(level, "[%d] Root: %d Children: %d", index,
                             *((int *)node->data), node->degree);
    if (node->child != NULL) {
        __dump_node(node->child, index, level + 1);
    }
}

/**
 * @brief Destructor for nodes in the root list
 */
void __free_node(void *node) { free((ntree_node *)node); }

/**
 * @brief Returns true if a is less than b (where a, b are fib heap elements)
 */
bool __is_less_than(fib_heap *fheap, void *a, void *b) {
    return fheap->__comparator(a, b) < 0;
}
