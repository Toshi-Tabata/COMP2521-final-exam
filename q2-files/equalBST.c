// equalBST.c ... implementation of equalBST function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "equalBST" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/



int equalBST(BSTree t1, BSTree t2) {
    // If t1 and t2 are NULL, return true
    if (t1 == NULL && t2 == NULL) return 1;

    // If either are NULL (but not both), then we have a mismatch
    if (t1 == NULL || t2 == NULL) return 0;

    if (key(t1) != key(t2)) return 0;

    // Checks left and right subtrees recursively (DFS manner)
    // Multiply answers so that only 1 false is required to return false
    return 1 * equalBST(t1->left, t2->left) * equalBST(t2->right, t2->right);
}

