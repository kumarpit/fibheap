#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>

// The type that the variable length array will contain. Defaults to int,
// but can really be anything.
#ifndef DA_TYPE
#define DA_TYPE
typedef int da_type;
#endif

#define INIT_CAPACITY 256

#define da_append(list, node)                                             \
    do {                                                                  \
        if (list.count >= list.capacity) {                                \
            if (list.capacity == 0) {                                     \
                list.capacity = INIT_CAPACITY;                            \
            } else {                                                      \
                list.capacity *= 2;                                       \
            }                                                             \
            list.items =                                                  \
                realloc(list.items, list.capacity * sizeof(*list.items)); \
        }                                                                 \
        list.items[list.count++] = node;                                  \
    } while (0)

#define da_is_empty(list) list.count == 0

#define da_for_each(list, item)                                              \
    for (size_t _i = 0; _i < (list).count && ((item) = (list).items[_i], 1); \
         _i++)

typedef struct {
    da_type *items;
    size_t count;
    size_t capacity;
} darray;

#endif
