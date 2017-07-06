static int tree_init(Tree *self) {
/*  Initializes a tree.

    Inputs: self - The Tree being initialized.

    Outputs: 0 If successful, else -1.
*/

    self->root = NULL;
    return 0;
}


static void tree_de_init(Tree *self) {
/*  De-allocates a tree.

    Inputs: self - The Tree being deinitialized.
*/

    Py_XDECREF(self->root);
    PyObject_Del(self);
}

