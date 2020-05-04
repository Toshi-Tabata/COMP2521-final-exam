// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* 
    You will submit only this one file.

    Implement the function "mergeOrdered" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

/*
    NOTES:

    Takes in 2 ordered lists (ascending order with duplicates)
    Returns a new list, in ascending order with duplicates
    - That contains all the values in both lists

    Requirements:
    - Must be O(m + n)
    - Doesn't have to be stable
    - Must not change original lists == additional space = (m + n) minimum
*/

/*
    Possible Algorithm:
    Merge sort?
    Traverse both lists at the same time and compare at each step

    // Below will break if either list is NULL - need to handle
    if list1 == list2:
        add both to new list
        list1++;
        list2++;
    elif list1 > list2:
        add list1 to newlist
        list1++;
    else:
        add list2 to newlist
        list2++;

    Time: O(n + m) as required (traverse both lists fully when m and n do not have overlaps)
        We do O(n + m) comparisons
    Space: O(n + m) additional space (store both lists in a new list)
        Use 2 pointers == O(1) space
    
    Cases:
    - List1 empty [] vs [1, 2, 3]
    - List2 empty [1, 2, 3] vs []
    - both empty [] vs []
    - 1 item in either/both lists  [1] vs [], [1] vs [1, 3, 7]
    - list1 = list2
    - list1 > list2
    - list2 > list1
    - duplicates in either/both lists
    - overlaps between the lists
*/

// Insert nodes at the end of the "new" list and updates first/last
static void insert(List new, int value) {
    if (new == NULL) return;

    Node *n = newNode(value);

    if (new->first == NULL) 
        new->first = n;
    else 
        new->last->next = n;
    
    new->last = n;
}

// Appends all the nodes starting from head to new
static void appendList(List new, Node *head) {
    while (head != NULL) {
        insert(new, head->value);
        head = head->next;
    }
}


List mergeOrdered(List list1, List list2) {
    List new = newList();

    Node *curr1 = list1->first;
    Node *curr2 = list2->first;

    // Traverse lists until one list is fully traversed O(min(len(m, n))) time
    while (curr1 != NULL && curr2 != NULL) {
        
        // curr1 is strictly smaller, add and increment only curr1
        if (curr1->value < curr2->value) {
            insert(new, curr1->value);
            curr1 = curr1->next;

        // Curr 2 is strictly smaller
        } else if (curr2->value < curr1->value) {
            insert(new, curr2->value);
            curr2 = curr2->next;

        // Curr 1 and 2 are equal, increment and add both
        } else {
            insert(new, curr1->value);
            insert(new, curr2->value);
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    }

    if (curr1 != NULL) {
        appendList(new, curr1);
    } else if (curr2 != NULL) {
        appendList(new, curr2);
    }

    return new;
}
