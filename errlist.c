/* errlist.c - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains functions for use with the
   error list.

*/


/************* Includes *******************/
#include "p4.h"
#include "errorlist.h"

/***************** Functions  ***************/

/* this function takes in a list pointer and a node pointer,
   and will then add the node to the list in order of line number */
void add_err(errlist *list, errnode *node)
{
    node->next = NULL;

    /* if head is null, make new node the head of the list */
    if (list->head == NULL)
    {
        list->head = node;
        list->count++;
    }
    else
    {

        /* is lineno before head? replace */
        if (node->lineno < list->head->lineno)
        {
            node->next = list->head;
            list->head = node;
            list->count++;
        }
        else
        {
            /* set the traversal node to head */
            list->cur = list->head;

            /* loop through list looking for insertion point */
            while (list->cur != NULL)
            {
                if (list->cur->next != NULL)
                {

                    if (node->lineno < list->cur->next->lineno)
                    {
                        /* found insertion point, add node in */
                        node->next = list->cur->next;
                        list->cur->next = node;
                        list->count++;
                        return;
                    }
                }
                else
                {
                    list->cur->next = node;
                    list->count++;
                    return;
                }
                list->cur = list->cur->next;
            }
            /* set last node's next pointer to our new node */
       //     list->cur->next = node;
          //  list->count++;
        }
    }
}

/* this function takes in a list pointer and will traverse through
  the list deleting nodes and then delete the list itself */
void delete_errlist(errlist* list)
{
    /*** Variables ***/
    errnode *temp = NULL; /* temp node to hold places */


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


