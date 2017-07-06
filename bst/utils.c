char _key_descent_compare(Node *node, PyObject *key) {
/*  Compares the given keys to determine which side the second key would lie relative to the first.
    This function shouldn't be used directly; the macro TREE_DESCENT_DIRECTION(node, key) should be used instead.

    Inputs: node - The node to compare the key against.
            key  - The key to compare against the node.

    Outputs: LEFT  if node.key >= key
             RIGHT if node.key < key
             -1    if an error occurred.
*/

    return PyObject_RichCompareBool(GET_KEY(a), key, Py_LT);
}

char _key_bound_compare(Node *node, PyObject *lower, PyObject *upper) {
/*  Compares the given key with the two bounds to determine if it satifies both.  A bound of NULL will be interpreted
    as being unbound in that direction.

    Inputs: node  - The node whose key should be compared against the bounds.
            lower - The lower bound to compare the key against.
            upper - The upper bound to compare the key against.

    Outputs: 0 If the key does not satisfy the lower bound.
             1 If the key does not satisfy the upper bound.
             2 If the key satisfies both bounds.
            -1 If an error occurred while comparing the key with the bounds.
*/

    char status;

    // Determine if the node satisfies the lower bound
    if (lower == NULL) {
        status = 1;
    } else {
        status = PyObject_RichCompareBool(GET_KEY(node), lower, Py_GE);
        if (status != 1)
            return status;
    }

    // Determine if the node satisfies the upper bound
    if (upper == NULL) {
        status = 1;
    } else {
        status = PyObject_RichCompareBool(GET_KEY(node), upper, Py_GT);
        if (status != 0)
            return status;
    }

    return 2;
}
