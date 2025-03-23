/**
 * \file
 * \brief Example usage for the FibHeap library
 */

#include <stdio.h>

#include "src/darray.h"
#include "src/fib_heap.h"
#include "src/utils.h"

/**
 * @brief Represents a 2-tuple structure
 */
typedef struct {
    int first;
    int second;
} pair;

/**
 * @brief Comparator for Pair structures which orders pairs based on their
 * `second` Value
 */
int cmp_pair(void *_a, void *_b) {
    pair *a = (pair *)_a;
    pair *b = (pair *)_b;
    return cmp_int(&(a->second), &(b->second));
}

/**
 * @brief Given a list of pairs {key, value} where value encodes the count of
 * its corresponding key, this method returns the top-K keys based on their
 * counts
 */
darray *top_k_frequent(darray *count_map, int k) {
    fib_heap *fheap = fib_heap_create(&cmp_pair);
    da_for_each(count_map) {
        fib_heap_push(fheap, _current);
        if (fheap->size > k) {
            fib_heap_pop(fheap);
        }
    }

    darray *res = da_create(NULL);
    while (!fib_heap_is_empty(fheap)) {
        da_append(res, &((pair *)fib_heap_pop(fheap))->first);
    }

    return res;
}

int main() {
    pair pairs[5];
    for (int i = 1; i <= 5; i++) {
        pairs[i - 1] = (pair){i, 6 - i};
    }

    // pairs: [{1, 5}, {2, 4}, {3, 3}, {4, 2}, {5, 1}]

    darray *count_map = da_create(NULL);
    for (int i = 0; i < 5; i++) {
        da_append(count_map, &pairs[i]);
    }

    // Expect Keys: 3, 2, 1
    darray *res = top_k_frequent(count_map, 3);
    da_for_each(res) { printf("Key: %d\n", *(int *)_current); }
}
