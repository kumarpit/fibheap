/**
 * This header file defines the interface to a fibonacci heap.
 */

#include <stdlib.h>
#include "ntree.h"

#define ROOT_LIST_INIT_CAPACITY 256;

/**
 * Fibonacci heaps store a list of n-ary tree structures. We represent this list with
 * the `root_list` type, which acts as a dynamic array.
 */

typedef struct {
    ntree_node **items;
    size_t count;
    size_t capacity;
} ntree_node_list;

#define da_append(list, node)                                                      \
    do                                                                             \
    {                                                                              \
        if (list.count >= list.capacity)                                           \
        {                                                                          \
            if (list.capacity == 0) {                                              \
                list.capacity = ROOT_LIST_INIT_CAPACITY;                           \
            } else {                                                               \
                list.capacity *= 2;                                                \
            }                                                                      \
            list.items = realloc(list.items, list.capacity * sizeof(*list.items)); \
        }                                                                          \
        list.items[list.count++] = node;                                           \
    } while (0)

/**
 * @brief Represents the fibnoacci heap structure. We store a pointer to the current minimum
 * root node, as well as a the root list.
 */
typedef struct {
    ntree_node *min;
    ntree_node_list root_list;
} fib_heap;

fib_heap *fib_heap_create();
void fib_heap_insert(fib_heap *, int);
int fib_heap_peek(fib_heap *);
int fib_heap_pop(fib_heap *);
