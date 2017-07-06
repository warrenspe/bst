Node *new_avl_node(PyObject *key, PyObject *data) {
/*  Initializes a new AVL tree Node.

    Inputs: key  - The key to assign to the node.
            data - An optional dictionary (or None) of attributes to associate with the node.

    Outputs: A pointer to the newly created node object, or NULL if an error occurred.
*/

    Node *node;

    if ((node = new_node(key, data)) == NULL)
        return NULL;

    SET_BALANCE(node, 0);

    return node;
}
