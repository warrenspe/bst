struct Tree {
    PyObject_HEAD
    // Root node in the tree
    Node *root;
    unsigned int count;
};

static PyMemberDef TreeMembers[] = {
    {"root", T_OBJECT, offsetof(Tree, root), READONLY, "Key of the node within the tree."},
    {"count", T_UINT, offsetof(Tree, count), READONLY, "Number of ndoes within the tree."},
    {NULL} // Sentinel
};

// TODO see about formatting the pydocstrs
static PyMethodDef TreeMethods[] = {
    {"add", (PyCFunction)tree_add_node, METH_VARARGS,
        PyDoc_STR("Adds a node to this table.")},
    {"get", (PyCFunction)tree_get_node, METH_VARARGS,
        PyDoc_STR("Retrieves a node from this table.")},
    {"get_range", (PyCFunction)tree_get_range, METH_VARARGS,
        PyDoc_STR("Retrieves nodes from this table between two optional bounds.")},
    {NULL}  // Sentinel
};


