struct Tree {
    PyObject_HEAD
    // Root node in the tree
    Node *root;

};

struct _itr_ctx {
    // The root node of our iteration
    Node *root;
    // The last returned 
    Node *curr;
    // The node returned previous to curr
    Node *last;
    // The last direction we traversed (UP, LEFT, RIGHT)
    char last_dir;

};

static PyMemberDef TreeMembers[] = {
    {"root", T_OBJECT, offsetof(Tree, root), READONLY, "Key of the node within the tree."},
    {NULL} // Sentinel
};

// TODO see about formatting the pydocstrs
static PyMethodDef TreeMethods[] = {
    {"add", (PyCFunction)tree_add_node, METH_VARARGS,
        PyDoc_STR("Adds a node to this table.")},
    {"get", (PyCFunction)tree_get_node, METH_VARARGS,
        PyDoc_STR("Retrieves a node from this table.")},
    {NULL}  // Sentinel
};


