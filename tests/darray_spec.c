#include <criterion/criterion.h>

#include "../src/darray.h"

Test(DynamicArray, create) {
    darray *new_arr = da_create();

    cr_assert_eq(NULL, new_arr->items);
    cr_assert_eq(0, new_arr->count);
    cr_assert_eq(0, new_arr->capacity);
}

Test(DynamicArray, append) {
    darray *arr = da_create();

    for (int i = 0; i < 3; i++) {
        da_append(arr, i);
    }

    for (int i = 0; i < 3; i++) {
        cr_assert_eq(i, da_get(arr, i));
    }
}

Test(DynamicArray, for_each) {
    darray *arr = da_create();

    for (int i = 0; i < 3; i++) {
        da_append(arr, i);
    }

    int i, count = 0;
    da_for_each(arr, i) {
        cr_assert_eq(count, i);
        count++;
    }
}
