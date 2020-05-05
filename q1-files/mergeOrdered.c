// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

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
    Time: O(n + m) as required (traverse both lists fully when m and n do not have overlaps)
        We do O(min(n + m)) comparisons
    Space: O(n + m) additional space (store both lists in a new list)
        Use 2 pointers O(1) space
    
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

static void insert(List new, int value);
static void appendList(List new, Node *head);

/*
    How the function works:

    1. Create a new list ("new")
    2. Make 2 pointers, curr1/curr2 (for list1/list2), starting from the start of the list
    3. Move pointer forward for minValue(curr1, curr2)
        - if they're equal, move both forward
    4. If we added all items from one list, add the rest of the other list to new
*/

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

    // Add the rest of the unfinished list
    if (curr1 != NULL) {
        appendList(new, curr1);
    } else if (curr2 != NULL) {
        appendList(new, curr2);
    }

    return new;
}


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
