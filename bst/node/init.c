static void node_de_init(Node *self) {
    /* De-allocates a Node. */

    Py_DECREF(self->key);
    Py_XDECREF(self->data);
    Py_XDECREF(self->left);
    Py_XDECREF(self->right);

    PyObject_Del(self);
}

