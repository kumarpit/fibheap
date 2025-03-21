/**
 * \file
 * \brief A simple dynamic array implementation
 */

#ifndef DARRAY_H
#define DARRAY_H

#include <stdbool.h>
#include <stdlib.h>

#define INIT_CAPACITY 256

#define da_append(list, node)                                                \
    do {                                                                     \
        if (list->count >= list->capacity) {                                 \
            if (list->capacity == 0) {                                       \
                list->capacity = INIT_CAPACITY;                              \
            } else {                                                         \
                list->capacity *= 2;                                         \
            }                                                                \
            list->items =                                                    \
                realloc(list->items, list->capacity * sizeof(*list->items)); \
        }                                                                    \
        list->items[list->count++] = (void *)node;                           \
    } while (0)

#define da_is_empty(list) list->count == 0

/**
 * Loops through every _NON-NULL_ value in the array
 */
#define da_for_each(list, item)                                          \
    for (size_t _i = 0;                                                  \
         _i < (list)->capacity && ((item) = (list)->items[_i], 1); _i++) \
        if (!((item) = (list)->items[_i]))                               \
            continue;                                                    \
        else
typedef struct {
    void **items;
    size_t count;
    size_t capacity;
} darray;

darray *da_create();
void *da_get(darray *, size_t);
void da_remove(darray *, size_t);
void da_set(darray *, void *, size_t);
void da_destroy(darray *, bool should_destroy_items);

#endif
