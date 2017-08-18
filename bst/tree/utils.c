void balance_tree(Tree *tree, Node *changed, char delta) {
/*  Balances the given tree using whichever balancing technique is appropriate for the type of tree.

    Inputs: tree    - The tree to balance.
            changed - A pointer to the node which is the root of the subtree which was modified.
            delta   - The change that was made to the tree.  One of ADDED, REMOVED.
*/

    Node *root = GET_ROOT(tree);

    // If the tree is empty .. there's nothing to balance
    if (root == NULL)
        return;

    if (Py_TYPE(tree) == &AVLTreeType) {
        balance_avl_tree(changed, delta);
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


PyObject *iterate_range(Tree *tree, PyObject *lower, PyObject *upper) {
/*  Iterates over the tree finding all nodes which fall between the two given ranges.

    Inputs: tree  - The tree to iterate over.
            lower - The lower bound of keys of nodes to include (inclusive).  If NULL no lower bound will be assumed.
            upper - The upper bound of keys of nodes to include (inclusive).  If NULL no upper bound will be assumed.

    Outputs: A PyList containing the nodes included in the iteration.
*/

    char bound_check,
         last_dir = LEFT;
    Node *root = GET_ROOT(tree),
         *current,
         *last;
    PyObject *list;

    // Find the first node in the range; this will be the root of our iteration
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

    current = root;
    last = root;
    if ((list = PyList_New(0)) == NULL)
        return NULL;

    while(1) {
        // If the left subtree is present and we didn't just iterate upwards to this node, test if we can iterate left
        if (GET_LEFT(current) != NULL && last_dir != UP) {
            if ((bound_check = TREE_BOUND_COMPARE(GET_LEFT(current), lower, upper)) == -1) {
                // If an error occurred
                Py_DECREF(list);
                return NULL;

            // If the left node satisfies the given bounds, descend!
            } else if (bound_check == 2) {
                last = current;
                current = GET_LEFT(current);
                last_dir = LEFT;
                continue;
            }
        }

        // Otherwise we can't descend left.  Add this node to the list if we didn't just iterate upwards from the right
        if (last_dir != UP || GET_RIGHT(current) != last)
            PyList_Append(list, (PyObject *) current);

        // If the right subtree is present and we didn't just iterate upwards from it, test if we can iterate right
        if (GET_RIGHT(current) != NULL && GET_RIGHT(current) != last) {
            if ((bound_check = TREE_BOUND_COMPARE(GET_RIGHT(current), lower, upper)) == -1) {
                // If an error occurred
                Py_DECREF(list);
                return NULL;

            // If the right node satisfies the given bounds, descend!
            } else if (bound_check == 2) {
                last = current;
                current = GET_RIGHT(current);
                last_dir = RIGHT;
                continue;
            }
        }

        // We can't descend at all.  Ascend, if we aren't the root node.
        if (current == root)
            return list;

        last = current;
        current = GET_PARENT(current);
        last_dir = UP;
    }

    return list;
}
