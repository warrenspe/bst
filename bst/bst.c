#include "headers/bst.h"

void init_types(PyObject *module) {
/* Initialize the Tree and Node class types.
 *
 * Inputs: module - The module object we will attach the types to.
 */

    if (PyType_Ready(&NodeType) < 0)
        return;
    if (PyType_Ready(&AVLTreeType) < 0)
        return;

    Py_INCREF(&NodeType);
    Py_INCREF(&AVLTreeType);
    PyModule_AddObject(module, "AVLTree", (PyObject *)&AVLTreeType);
}


static PyMethodDef bstMethods[] = {
    {NULL, NULL, 0, NULL}   /* sentinel */
};


#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef bstDef = {
    PyModuleDef_HEAD_INIT,
    "bst",
    "Package containing a binary search tree implementation.",
    -1,
    bstMethods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_bst(void) {
    PyObject *module = PyModule_Create(&bstDef);
    init_types(module);
    return module;
}

#else
PyMODINIT_FUNC initbst(void) {
    PyObject *module = Py_InitModule3("bst", bstMethods, "Package containing a binary search tree implementation.");
    init_types(module);
}
#endif

