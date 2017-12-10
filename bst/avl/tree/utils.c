void balance_avl_tree(Node *curr, char delta) {
/*  Recursively balances the tree from a given node and upwards all the way (if necessary) to the root node.
    Performs whichever balances are necessary.  This function should not be used directly.  Instead use the macros:
    BALANCE_ADDED(tree, parent_of_added_node), BALANCE_REMOVED(tree, parent_of_removed_node).

    Inputs: curr  - The node to begin the balancing from; the parent of a node which was added/removed.
            delta - The change that was made to the tree.  One of ADDED, REMOVED
*/

    if (curr == NULL)
        return;

    // If the tree is right-heavy, balance it and return.  After balancing all uptree nodes are balanced.
    if (GET_BALANCE(curr) < -1) {
        // If the right subtree is left-heavy, rotate it right
        if (GET_BALANCE(GET_RIGHT(curr)) > 0)
            ROTATE_RIGHT(GET_RIGHT(curr));
        ROTATE_LEFT(curr);
        return;

    // Else if the tree is left-heavy, balance it and return.  After balancing all uptree nodes are balanced
    } else if (GET_BALANCE(curr) > 1) {
        // If the left subtree is right-heavy, rotate it left
        if (GET_BALANCE(GET_LEFT(curr)) < 0)
            ROTATE_LEFT(GET_LEFT(curr));
        ROTATE_RIGHT(curr);
        return;
    }

    // After rotating, the current curr node will now be the child of the previous curr node
    curr = GET_PARENT(curr);

    // If we're here, we did not balance the tree.  (In/De)crement our parents balance depending on what type of a child
    // we are and continue balancing up the tree
    if (GET_PARENT(curr) != NULL) {
        // If we are a left child of our parent we need to flip our delta to fit the following:
        //          LEFT | RIGHT
        // add    |   +1 |    -1
        // remove |   -1 |    +1
        SET_BALANCE(GET_PARENT(curr), (CHILD_TYPE(curr) == LEFT ? -delta : delta));

        // Recursively perform balancing on the parent if we haven't just balanced it.
        if (GET_BALANCE(GET_PARENT(curr)) != 0)
            balance_avl_tree(GET_PARENT(curr), delta);
    }
}
