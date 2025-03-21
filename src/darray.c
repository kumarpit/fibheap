#include "darray.h"

#include <assert.h>

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
da_type da_get(darray *da, int index) {
    assert(da != NULL);
    assert(da->items != NULL);

    // TODO: add bounds checking
    return da->items[index];
}

/**
 * @brief Destroys the array and optionally all the items contained within it
 */
void da_destroy(darray *da, bool should_destroy_items) {
    if (should_destroy_items) {
        // TODO: would need to store a function pointer to a custom free
        // function
    }
    free(da);
}
