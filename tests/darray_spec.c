#include <criterion/criterion.h>

#include "../src/darray.h"

Test(DynamicArray, create) {
    darray *new_arr = da_create(NULL);

    cr_assert_eq(NULL, new_arr->items);
    cr_assert_eq(0, new_arr->count);
    cr_assert_eq(0, new_arr->capacity);
}

Test(DynamicArray, append) {
    darray *arr = da_create(NULL);

    int values[3];
    int *ptrs[3];

    for (int i = 0; i < 3; i++) {
        values[i] = i;
        ptrs[i] = &values[i];
    }

    for (int i = 0; i < 3; i++) {
        da_append(arr, ptrs[i]);
    }

    for (int i = 0; i < 3; i++) {
        cr_assert_eq(ptrs[i], da_get(arr, i));
    }
}

Test(DynamicArray, for_each) {
    darray *arr = da_create(NULL);

    int values[3];
    int *ptrs[3];

    for (int i = 0; i < 3; i++) {
        values[i] = i;
        ptrs[i] = &values[i];
    }

    for (int i = 0; i < 3; i++) {
        da_append(arr, ptrs[i]);
    }

    int *i;
    da_for_each(arr, i) { cr_assert_eq(values[_i], *i); }
}
