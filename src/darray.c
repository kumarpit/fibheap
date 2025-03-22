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

    // NOTE: not checking with count because our array may have gaps because we
    // support removing elements at arbitrary indices
    if (index >= da->capacity) {
        debug_error("index %zu out of bounds (size: %zu)", index, da->count);
        exit(1);
    }

    return (void *)da->items[index];
}

/**
 * @brief Mutate the element at the given index
 */
void da_set(darray *da, void *data, size_t index) {
    assert(da != NULL);
    assert(da->items != NULL);
    da->items[index] = data;
}

/**
 * @brief Remove the element at the given index
 */
void da_remove(darray *da, size_t index) {
    free(da_get(da, index));
    da_set(da, NULL, index);
    da->count--;
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
