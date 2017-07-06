// Generic Node Macros
#define CHILD_TYPE(node) (node->parent != NULL && node->parent->left == node ? LEFT : RIGHT)

#define GET_PARENT(node) (node->parent)
#define GET_KEY(node) (node->key)
#define GET_CHILD(node, dir) (dir == LEFT ? GET_LEFT(node) : GET_RIGHT(node))
#define GET_OTHER_CHILD(node, dir) GET_CHILD(node, !dir)
#define GET_LEFT(node) (node->left)
#define GET_RIGHT(node) (node->right)
#define GET_LINK(node, dir) (dir == UP ? GET_PARENT(node) : GET_CHILD(node, dir))

#define SET_CHILD(node, child, side) _node_set_child(node, child, side)
#define SET_LEFT(node, left) SET_CHILD(node, left, LEFT)
#define SET_RIGHT(node, right) SET_CHILD(node, right, RIGHT)

#define ROTATE(node, dir) _node_single_rotation(node, dir)
#define ROTATE_LEFT(node) ROTATE(node, LEFT)
#define ROTATE_RIGHT(node) ROTATE(node, RIGHT)

#define CTX_INIT_ITERATE(_root) {.root = _root, .curr = _root, .last = _root, .last_action = DOWN}


// AVLNode Macros
#define GET_BALANCE(node) (node->_prop)
#define SET_BALANCE(node, val) node->_prop = val

#define BALANCE_ADDED(node) _balance_tree(node, -1)
#define BALANCE_REMOVED(node) _balance_tree(node, 1)

// Generic Tree Macros
#define GET_ROOT(tree) (tree->root)
#define SET_ROOT(tree, root) tree->root = root

#define TREE_DESCENT_DIRECTION(treenode, search_key) _key_descent_compare(treenode, search_key)
#define TREE_BOUND_COMPARE(treenode, lower, upper) _key_bound_compare(treenode, lower, upper)
