#ifndef __BST_H
#define __BST_H 1

    // TODO staticify everything that shouldn't ever be referenced outside of us

    // Global Defines
    #define LEFT 0
    #define RIGHT 1
    #define UP 2

    #define ADDED -1
    #define REMOVED 1

    // Library Includes
    #include <Python.h>
    #include "structmember.h"
    #include <stdlib.h>

    // Declarations for DLL import/export
    #ifndef PyMODINIT_FUNC
        #define PyMODINIT_FUNC void
    #endif

    // Definitions
    #include "headers/definitions.h"

    // Type Includes
    #include "headers/node.h"
    #include "headers/tree.h"
    #include "headers/avl_tree.h"

    // Macro Includes
    #include "headers/macros.h"

    // Source Includes
    #include "utils.c"

    #include "node/init.c"
    #include "node/utils.c"

    #include "tree/init.c"
    #include "tree/utils.c"
    #include "tree/operations.c"

    #include "avl/node/utils.c"

    #include "avl/tree/utils.c"

#endif
