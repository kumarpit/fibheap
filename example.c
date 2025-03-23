/**
 * \file
 * \brief
 */

#include "src/darray.h"
#include "src/debug.h"
#include "src/fib_heap.h"
#include "src/utils.h"

typedef struct {
    int first;
    int second;
} pair;

int cmp_pair(void *_a, void *_b) {
    pair *a = (pair *)_a;
    pair *b = (pair *)_b;
    return -cmp_int(&(a->second),
                    &(b->second));  // NOTE: -ve to make this a max heap
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

int main() {
    pair pairs[5];
    for (int i = 1; i <= 5; i++) {
        pairs[i - 1] = (pair){i, 6 - i};
    }

    darray *count_map = da_create(NULL);
    for (int i = 0; i < 5; i++) {
        da_append(count_map, &pairs[i]);
    }

    darray *res = top_k_frequent(count_map, 3);
    da_for_each(res) {
        debug_printf("Key: %d Value: %d", ((pair *)_current)->first,
                     ((pair *)_current)->second);
    }
}
