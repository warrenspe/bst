// bst.c Definitions
#if PY_MAJOR_VERSION >= 3
    PyMODINIT_FUNC PyInit_bst(void);
#else
    PyMODINIT_FUNC initbst(void);
#endif
void init_types(PyObject *);

// Struct Definitions
typedef struct Node Node;
typedef struct Tree Tree;

static typedef struct _itr_ctx _itr_ctx;


/*
    Generic Definitions
*/

// utils.c
char _key_compare(PyObject *, PyObject *);


// node/init.c
static void node_de_init(Node *);


// node/utils.c
Node *new_node(PyObject *, PyObject *);
void _node_set_child(Node *, Node *, unsigned char);
void _node_single_rotation(Node *, unsigned char);


// tree/init.c
static int tree_init(Tree *);
static void tree_de_init(Tree *);


// tree/operations.c


/*
    AVL-specific Definitions
*/

// avl/node/utils.c
Node *new_avl_node(PyObject *, PyObject *);


// avl/tree/utils.c
void balance_avl_tree(Node *, char);
