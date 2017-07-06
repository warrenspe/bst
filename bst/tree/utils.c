void balance_tree(Tree *tree, node *changed, char delta) {
/*  Balances the given tree using whichever balancing technique is appropriate for the type of tree.

    Inputs: tree    - The tree to balance.
            changed - A pointer to the node which is the root of the subtree which was modified.
            delta   - The change that was made to the tree.  One of ADDED, REMOVED.
*/

    Node *root = GET_ROOT(tree),

    // If the tree is empty .. there's nothing to balance
    if (root == NULL)
        return;

    switch (((PyObject *) tree)->ob_type) {
        case &AVLTreeType:
            balance_avl_tree(changed, delta);
            break;
    }

    // Check if the root node has a non-NULL parent.  If so, it was rebalenced down.  Find the new root node.
    while (GET_PARENT(root) != NULL)
        root = GET_PARENT(root);

    SET_ROOT(tree, root);
}


Node *descend_tree(Tree *tree, PyObject *key, char *dir) {
/*  Find the lowest node in the tree which binary descent results in.

    Inputs: tree - The tree to descend.
            key  - The key to search for in the tree
            dir  - A pointer to a char which will be populated with the side of the returned node, which descent would
                   have continued if it were able to.

    Outputs: The found node.
             NULL & a dir of 0 if the tree is empty.
             NULL & a dir of -1 if an error occurred during descent.
*/

    Node *current = NULL,
         *next = GET_ROOT(tree);

    *dir = 0;

    while (next != NULL) {
        current = next;

        // Determine which way to descend
        if ((*dir = TREE_DESCENT_DIRECTION(current, key)) == -1)
            return NULL;

        next = GET_CHILD(current, *dir);
    }

    return current;
}

static Node *_iterate_children(_itr_ctx *context, char prevent) {
/*  Iterates over all of the children, in order, below a subtree identified by the given root node.

    Note: To initialize the context, use the macro: _CTX_ITERATE_INIT(root_node)

    Inputs: context - A pointer to an _itr_ctx object which will be used to store context of our iteration.
            prevent - A char which can be used to prevent descent down a particular subtree of the current node.
                      One of: -1: No override; LEFT: Prevent iteration down left; RIGHT: Prevent iteration down right

    Outputs: A Node object of the next node in the iteration, or NULL if no more nodes remain.
*/

    char dir = UP;

    // If we last iterated upwards, we either just came from the left or right subtree.
    if (context->last_dir == UP) {
        // We only consider descending down the right subtree if we just came up from the left subchild,
        // right isn't NULL, and we weren't prevented from iterating down the right branch
        // Otherwise, if we came up from the right or one of the above is false, we will continue iteration upwards.
        if (context->last == GET_LEFT(context->curr) && prevent != RIGHT && GET_RIGHT(context->curr) != NULL) {
            dir = RIGHT;

    // Else we last iterated downwards from curr's parent.
    } else {
        // If we're allowed to, check the current node's left subtree
        if (GET_LEFT(context->curr) != NULL && prevent != LEFT) {
            dir = LEFT;

        // Otherwise check the current node's right subtree
        } else if (GET_RIGHT(context->curr) != NULL && prevent != RIGHT) {
            dir = RIGHT;

        // Otherwise, we have no choice but to iterate back upwards, which is what dir is already set to.
        }
    }

    // Validate that we are not about to transition above our root node, and that wherever we're about to transition
    // exists. If one of these is about to happen, return NULL to signify end of iteration.
    if ((dir == UP && context->curr == context->root))
        return NULL;

    // Set curr, last, and last_action appropriately
    context->last = context->curr;
    context->curr = GET_LINK(context->curr, dir);
    context->last_dir = dir;

    return context->curr;
}


PyObject *iterate_range(Tree *tree, PyObject *lower, PyObject *upper) {
/*  Iterates over the tree finding all nodes which fall between the two given ranges.

    Inputs: tree  - The tree to iterate over.
            lower - The lower bound of keys of nodes to include (inclusive).  If NULL no lower bound will be assumed.
            upper - The upper bound of keys of nodes to include (inclusive).  If NULL no upper bound will be assumed.

    Outputs: A PyList containing the nodes included in the iteration.
*/

    char prevent_side,
         bound_check;
    Node *root = GET_ROOT(tree),
         *current;
    PyObject *list;
    _itr_ctx iteration_context;

    // Find the first node in the range
    while (root != NULL) {
        switch(TREE_BOUND_COMPARE(root, lower, upper)) {
            // If an error occurred
            case -1:
                return NULL;

            // Satisfies upper bound but not lower; descend right
            case 0:
                root = GET_RIGHT(root);
                continue;

            // Satisfies lower bound but not upper; descend left
            case 1:
                root = GET_LEFT(root);
                continue;

            // Satisfies both bounds.  Break out of the switch & while
            case 2:
                break;
        }
        break;
    }

    iteration_context = CTX_INIT_ITERATE(root);
    current = root;
    if ((list = PyList_New(0)) == NULL)
        return NULL;

    // Add the nodes within the bounds below this node to the list
    while (current != NULL) {
        prevent_side = -1;
        // Determine if the current node we're looking at it is outside the given bounds
        bound_check = TREE_BOUND_COMPARE(current, lower, upper);
        // Check if an error occurred
        if (bound_check == -1) {
            Py_DECREF(list);
            return NULL;

        // If the current node is to the left of the bounds

        // Check if current is within the bounds
        } else if (bound_check == 2) {

        // Otherwise, force the iterator to ascend up a level - as if 
        }
        // If it is (bound_check != 2), then force the iterator to ascend up a level
        force_up = (bound_check != 2);
        

        current = _iterate_children(iteration_context, force_up)
    }

    return list;
}
