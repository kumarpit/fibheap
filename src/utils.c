//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Helpful methods when dealing with int* as the heap data type
//
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief A comparison function for int pointers
 * @returns -1 if *a  <  *b
 *           1 if *a  >  *b
 *           0 if *a  =  *b
 */
int cmp_int(void *_a, void *_b) {
    int *b = (int *)_b;
    int *a = (int *)_a;
    return (*a > *b) - (*a < *b);
}

/**
 * @brief Cast to int* and dereference a void pointer
 */
int to_int(void *ptr) { return *((int *)ptr); }
