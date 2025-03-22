#include "darray.h"

#include <assert.h>

#include "debug.h"

/**
 * @brief Initializes a new dynamic array
 */
darray *da_create() {
    darray *new_darray = malloc(sizeof(darray));
    new_darray->items = NULL;
    new_darray->count = 0;
    new_darray->capacity = 0;

    return new_darray;
}

/**
 * @brief Gets the item at index from the array with bounds checking
 */
void *da_get(darray *da, size_t index) {
    assert(da != NULL);
    assert(da->items != NULL);

    // if (index >= da->count) {
    //     debug_error("index %zu out of bounds (size: %zu)", index, da->count);
    //     exit(1);
    // }
    //
    return (void *)da->items[index];
}

void da_set(darray *da, void *data, size_t index) {
    assert(da != NULL);
    assert(da->items != NULL);
    da->items[index] = data;
}

/**
 * @brief Destroys the array and optionally all the items contained within it
 */
void da_destroy(darray *da, bool should_destroy_items) {
    if (should_destroy_items) {
        for (size_t i = 0; i < da->count; ++i) {
            if (da->items[i] == NULL) continue;
            // TODO: possibly pass in a custom free function
            free(da->items[i]);
        }
    }
    free(da);
}
