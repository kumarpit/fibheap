#include "darray.h"

#include <assert.h>
#include <stdbool.h>

#include "debug.h"

// Forward declarations (private methods)
bool __is_index_in_bounds(darray *, size_t index);

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// DArray interface implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes a new dynamic array
 */
darray *da_create(free_func __free) {
    darray *new_darray = malloc(sizeof(darray));
    new_darray->items = NULL;
    new_darray->count = 0;
    new_darray->capacity = 0;
    new_darray->__free = __free;

    return new_darray;
}

/**
 * @brief Gets the item at index from the array with bounds checking
 */
void *da_get(darray *da, size_t index) {
    assert(da != NULL);
    assert(da->items != NULL);
    assert(__is_index_in_bounds(da, index));

    return (void *)da->items[index];
}

/**
 * @brief Mutate the element at the given index
 */
void da_set(darray *da, void *data, size_t index) {
    assert(da != NULL);
    assert(da->items != NULL);
    assert(__is_index_in_bounds(da, index));

    da->items[index] = data;
}

/**
 * @brief Remove the element at the given index
 */
void da_remove(darray *da, size_t index, bool should_destroy_item) {
    if (should_destroy_item) {
        void *item = da_get(da, index);

        assert(item != NULL);
        assert(da->__free != NULL);

        da->__free(item);
    }
    da_set(da, NULL, index);
    da->count--;
}

/**
 * @brief Destroys the array and optionally all the items contained within it
 */
void da_destroy(darray *da, bool should_destroy_items) {
    if (should_destroy_items) {
        assert(da->__free != NULL);
        da_for_each(da) { da->__free(_current); };
    }
    free(da);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Private method definitions
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Returns true if the given index is valid (i.e lies within the
 * allocated region), false otherwise
 */
inline bool __is_index_in_bounds(darray *da, size_t index) {
    // NOTE: not checking with count because our array may have gaps because we
    // support removing elements at arbitrary indices
    if (index >= da->capacity) {
        debug_error("index %zu out of bounds (size: %zu)", index, da->count);
        return false;
    }
    return true;
}
