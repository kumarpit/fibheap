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
 * @brief Custom comparator for fib_heap elements
 * @returns -1 if a  <  b
 *           0 if a ==  b
 *           1 if a  >  b
 */
typedef int (*cmp_func)(void *a, void *b);

/**
 * @brief Represents the fibnoacci heap structure. We store a pointer to the
 * current minimum root node, as well as a the root list.
 */
typedef struct {
    int min_index;
    int size;
    cmp_func __comparator;
    ntree_node_list *root_list;
} fib_heap;

fib_heap *fib_heap_create(cmp_func);
bool fib_heap_is_empty(fib_heap *);
int fib_heap_root_size(fib_heap *);

ntree_node *fib_heap_push(fib_heap *, void *);
void *fib_heap_peek(fib_heap *);
void *fib_heap_pop(fib_heap *);

void fib_heap_merge(fib_heap *self, fib_heap *other);
void fib_heap_decrease_key(fib_heap *fheap, ntree_node *, void *);
void fib_heap_dump(fib_heap *);

#endif
