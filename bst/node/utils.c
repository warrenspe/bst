Node *new_node(PyObject *key, PyObject *data) {
/*  Initializes a new Node.

    Inputs: key   - The key to assign to the node.
            data  - An optional dictionary (or None) of attributes to associate with the node.

    Outputs: A pointer to the newly created node object, or NULL if an error occurred.
*/

    Node *node;

    if ((node = PyObject_New(Node, &NodeType)) == NULL)
        return NULL;

    PyErr_Clear();
    PyObject_Init((PyObject *)node, &NodeType);
    if (PyErr_Occurred() != NULL) {
        PyObject_Del(node);
        return NULL;
    }

    node->key = key;
    node->data = data;

    node->parent = NULL;
    SET_LEFT(node, NULL);
    SET_RIGHT(node, NULL);

    Py_INCREF(key);
    Py_XINCREF(data);

    return node;
}


void _node_set_child(Node *self, Node *child, unsigned char side) {
/*  Sets a child of the given node.  This function should not be used directly.  Instead, use one of the macros:
    SET_LEFT(node, left), SET_RIGHT(node, right), SET_CHILD(node, child, side).

    Inputs: self  - The node to set the child of.
            child - The node to set as the child.
            side  - A boolean indicating which side the child should be set on.  See bst.h for defines
*/

    if (child != NULL)
        child->parent = self;

    if (self != NULL) {
        if (side == LEFT) {
            self->left = child;
            
        } else {
            self->right = child;
        }
    }
}


void _node_single_rotation(Node *self, unsigned char dir) {
/*  Rotates a node to the left or right.  This function should not be used directly.  Instead use the macros:
    ROTATE_LEFT(node), ROTATE_RIGHT(node), ROTATE(node, direction).

    Inputs: self - The first pivot node to rotate.  Note that neither this, nor the other pivot can be NULL.
            dir  - A boolean indicating which direction the node will be rotated.  See bst.h for defines
*/

    Node *pivot = GET_OTHER_CHILD(self, dir),
         *parent = GET_PARENT(self);
    unsigned char parentSide = CHILD_TYPE(self);

    if (dir == LEFT) {
        SET_RIGHT(self, GET_LEFT(pivot));
        SET_LEFT(pivot, self);
    } else {
        SET_LEFT(self, GET_RIGHT(pivot));
        SET_RIGHT(pivot, self);
    }
    SET_CHILD(parent, pivot, parentSide);
}
