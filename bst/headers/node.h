struct Node {
    PyObject_HEAD
    // Key of the node within the table
    PyObject *key;
    // Extra data associated with the node
    PyObject *data;
    // Parent of this object, or NULL if root.
    Node *parent;
    // Left child, or NULL
    Node *left;
    // Right child, or NULL
    Node *right;
    // Internal attribute, used to store attributes of the node for the various tree types
    char _prop;
};

static PyMemberDef NodeMembers[] = {
    {"key", T_OBJECT_EX, offsetof(Node, key), READONLY, "Key of the node within the tree."},
    {"data", T_OBJECT, offsetof(Node, data), 0, "Extra data associated with the node."},
    {"left", T_OBJECT, offsetof(Node, left), READONLY, "Right child of this node."},
    {"right", T_OBJECT, offsetof(Node, right), READONLY, "Left child of this node."},
    {"parent", T_OBJECT, offsetof(Node, parent), READONLY, "Parent of this node."},
    {NULL} // Sentinel
};

static PyMethodDef NodeMethods[] = {
    {NULL}  // Sentinel
};


static PyTypeObject NodeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "bst.Node",
    sizeof(Node),
    0,                         /*tp_itemsize*/
    (destructor)node_de_init,  /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "bst.Node object.",        /*tp_doc*/
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    NodeMethods,               /* tp_methods */
    NodeMembers,               /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,                         /* tp_init */
    0,                         /* tp_alloc */
    PyType_GenericNew,         /* tp_new */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};
