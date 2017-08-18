char _key_descent_compare(PyObject *first, PyObject *second) {
/*  Compares the given keys to determine which side the second key would lie relative to the first.
    This function shouldn't be used directly; the macro TREE_DESCENT_DIRECTION(node, key) should be used instead.

    Inputs: first  - The first key to compare.
            second - The second key to compare.

    Outputs: LEFT  if first >= second
             RIGHT if first < second
             -1    if an error occurred.
*/

    return PyObject_RichCompareBool(first, second, Py_LT);
}

char _key_bound_compare(PyObject *key, PyObject *lower, PyObject *upper) {
/*  Compares the given key with the two bounds to determine if it satifies both.  A bound of NULL will be interpreted
    as being unbound in that direction.

    Inputs: key   - The key which should be compared against the bounds.
            lower - The lower bound to compare the key against.
            upper - The upper bound to compare the key against.

    Outputs: 0 If the key does not satisfy the lower bound.
             1 If the key does not satisfy the upper bound.
             2 If the key satisfies both bounds.
            -1 If an error occurred while comparing the key with the bounds.
*/

    char status;

    // Determine if the key satisfies the lower bound
    if (lower != NULL) {
        status = PyObject_RichCompareBool(key, lower, Py_GE);
        if (status != 1)
            return status;
    }

    // Determine if the key satisfies the upper bound
    if (upper != NULL) {
        status = PyObject_RichCompareBool(key, upper, Py_GT);
        if (status != 0)
            return status;
    }

    return 2;
}
