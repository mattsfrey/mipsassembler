/* dataentry.c - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains functions for use with the
   data entry list.

*/

/************** Includes ********************/
#include "dataentry.h"


/***************** Functions ******************/

/* this function takes in a list pointer and a node pointer,
   and will then add the node to the end of the list */
void add_datanode(datalist *list, datanode *node)
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
  the list deleting nodes and then delete the list itself */
void delete_datalist(datalist* list)
{
    /*** Variables ***/
    datanode *temp = NULL; /* temp node to hold places */


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

