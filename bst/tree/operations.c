PyObject *tree_add_node(Tree *self, PyObject *args, PyObject *kwargs) {
/*  Add a node to the tree.

    Inputs: self   - The tree to add the node to.
            args   - A PyTuple containing arguments (see below).
            kwargs - A PyDict containing arguments (see below).

    Accepts two positional/keyword arguments:
        Required:
            key - A PyObject to associate with this node.  Will be used to order the tree.
        Optional:
            data - An extra PyObject to associate with this node.

    Outputs: PyNone.
*/

    PyObject *key,
             *data;

    Node *node,
         *parent;
    char dir;

    static char *kwlist[] = {"key", "data", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|O", kwlist, &key, &data))
        return NULL;

    // Get the parent node of the node to add
    if ((parent = descend_tree(self, key, &dir)) == NULL && dir == -1)
        return NULL;

    if ((node = new_node(key, data)) == NULL)
        return NULL;


    // Edge case - if the tree is empty; this new node is our new root.
    if (GET_ROOT(self) == NULL) {
        SET_ROOT(self, node);

    // Add the node to its appropriate slot
    } else {
        SET_CHILD(parent, node, dir);
    }

    // Rebalance the tree
    BALANCE_ADDED(self, parent);

    // Increment the tree's node count
    self->count++;

    Py_RETURN_NONE;
}

PyObject *tree_get_node(Tree *self, PyObject *args, PyObject *kwargs) {
/*  Retrieves a node from the tree.

    Inputs: self   - The tree to get the node to.
            args   - A PyTuple containing arguments (see below).
            kwargs - A PyDict containing arguments (see below).

    Accepts one positional/keyword arguments:
        Required:
            key - The PyObject of the key contained by the node we are to find and return.

    Outputs: Py_None.
*/

    PyObject *key;

    Node *node;
    char status;

    static char *kwlist[] = {"key", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &key))
        return NULL;

    if ((node = descend_tree(self, key, &status)) == NULL && status == -1)
        return NULL;

    // Check if we found a node having the same key as the lookup key.  If so return it, else return None
    if ((status = PyObject_RichCompareBool(GET_KEY(node), key, Py_EQ)) == -1)
        return NULL;

    if (status == 1)
        return (PyObject *)node;

    Py_RETURN_NONE;
}

PyObject *tree_get_range(Tree *self, PyObject *args, PyObject *kwargs) {
/*  Retrieves a range of nodes from the tree based on the lookup keys.

    Inputs: self   - The tree to get the node to.
            args   - A PyTuple containing arguments (see below).
            kwargs - A PyDict containing arguments (see below).

    Accepts one positional/keyword arguments:
        Required:
            lower - The lower bound on the lookup key, or PyNone.
            upper - The upper bound on the lookup key, or PyNone.

    Outputs: A PyList containing the nodes in the tree which satisfy the given bounds.
*/

    PyObject *lower,
             *upper;
    static char *kwlist[] = {"lower", "upper", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO", kwlist, &upper, &lower))
        return NULL;

    // Convert Py_None -> NULL
    if (lower == Py_None)
        lower = NULL;
    if (upper == Py_None)
        upper = NULL;

    return iterate_range(self, lower, upper);

}
