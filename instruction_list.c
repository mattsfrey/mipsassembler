/* instruction_list.c - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains the functions used to facilitate
   the linked list that will hold all the assembly instructions
*/


/*********** Includes *******************/

#include "instruction_list.h"


/*************** functions ***********************/

/* this function takes in a list pointer and a node pointer,
   and will then add the node to the end of the list */
void add_node(instlist *list, instnode *node)
{
    /* if head is null, make new node the head of the list */
    if (list->head == NULL)
    {
        list->head = node;
        list->count++;
    }
    else
    {
        /* set the traversal node to head */
        list->cur = list->head;

        /* loop to end of list */
        while (list->cur->next != NULL)
        {
            list->cur = list->cur->next;
        }
        /* set last node's next pointer to our new node */
        list->cur->next = node;
        list->count++;
    }
}

/* this function takes in a list pointer and will traverse through
  the list deleting nodes and then delte itself */
void delete_list(instlist* list)
{
    /*** Variables ***/
    instnode *temp = NULL; /* temp node to hold places */


    if (list->head != NULL)
    {
        list->cur = list->head;
        while (list->cur != NULL)
        {
            temp = list->cur;
            list->cur = list->cur->next;
            free(temp);
        }
    }
    free(list);
}


