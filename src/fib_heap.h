/**
 * This header file defines the interface to a fibonacci heap.
 */

#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <stdlib.h>

#include "ntree.h"

#define DA_TYPE
typedef ntree_node *da_type;
#include "darray.h"

/**
 * Fibonacci heaps store a list of n-ary tree structures. We represent this list
 * with the `ntree_node_list` type, which is implemented as a dynamic array.
 */
typedef darray ntree_node_list;

/**
 * @brief Represents the fibnoacci heap structure. We store a pointer to the
 * current minimum root node, as well as a the root list.
 */
typedef struct {
    ntree_node *min;
    ntree_node_list root_list;
} fib_heap;

fib_heap *fib_heap_create();
void fib_heap_insert(fib_heap *, int);
int fib_heap_peek(fib_heap *);
int fib_heap_pop(fib_heap *);

#endif
