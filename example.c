/**
 * \file
 * \brief
 */

#include "darray.h"
#include "fib_heap.h"
#include "src/utils.h"

typedef struct {
    int first;
    int second;
} pair;

int cmp_pair(void *_a, void *_b) {
    pair *a = (pair *)_a;
    pair *b = (pair *)_b;
    return cmp_int(&(a->second), &(b->second));
}

darray *top_k_frequent(darray *count_map, int k) {
    fib_heap *fheap = fib_heap_create(&cmp_pair);
    da_for_each(count_map) {
        fib_heap_push(fheap, _current);
        if (fib_heap_size(fheap) > k) {
            fib_heap_pop(fheap);
        }
    }

    darray *res = da_create(NULL);
    while (!fib_heap_is_empty(fheap)) {
        da_append(res, fib_heap_pop(fheap));
    }

    return res;
}

int main() { return 0; }
