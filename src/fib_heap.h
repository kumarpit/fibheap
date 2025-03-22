/**
 * \file
 * \brief Defines the interface to a fibonacci heap
 */

#ifndef FIB_HEAP_H
#define FIB_HEAP_H

#include <stdlib.h>

#include "darray.h"
#include "ntree.h"

/**
 * Fibonacci heaps store a list of n-ary tree structures. We represent this list
 * with the `ntree_node_list` type, which is implemented as a dynamic array.
 */
typedef darray ntree_node_list;

/**
 * The max degree of a tree in our fibonacci heap
 */
#define FIB_HEAP_MAX_DEGREE 64

/**
 * @brief Represents the fibnoacci heap structure. We store a pointer to the
 * current minimum root node, as well as a the root list.
 */
typedef struct {
    int min_index;
    ntree_node_list *root_list;
} fib_heap;

fib_heap *fib_heap_create();

void fib_heap_insert(fib_heap *, int);
int fib_heap_peek(fib_heap *);
int fib_heap_pop(fib_heap *);

// TODO:
/*fib_heap *fib_heap_merge(...);*/
/*void fib_heap_decrease_key(...);*/
void fib_heap_dump(fib_heap *);

#endif
