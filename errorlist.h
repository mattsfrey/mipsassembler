/* errorlist.h - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains data structure definition and
   function prototypes for the error list

*/


#ifndef ERRORLIST_H_INCLUDED
#define ERRORLIST_H_INCLUDED


/***************** Includes ******************/
#include "p4.h"
#include "instruction_list.h"

/****************** Constants **************/

#define ERR_OPCODE 0       /* illegal opcode detected */
#define ERR_UNDEFSYMBOL 1  /* undefined symbol used   */
#define ERR_MULTSYMBOL 2   /* mutiply defined symbold */

/****************** Data Structures ********************/

/* this node will hold an error found
   while reading asm file */
typedef struct errnode_s
{
    /* variables */
    int errtype;             /* type of error */
    int lineno;              /* line number error was encountered on */

    char symbol[LABEL_LEN];  /* name of symbol */
    char opcode[OPCODE_LEN]; /* name of opcode */


    struct errnode_s *next; /* pointer to next node in list */

} errnode;

typedef struct errlist_s
{
    errnode *head;  /* pointer to the head of the list */
    errnode *cur;   /* node pointer used for traversal */

    int count;       /* number of instructions */

} errlist;


/*************** Functions **************************************/

/* add a node to list */
void add_err(errlist *list, errnode *node);

/* delete the list */
void delete_errlist(errlist *list);


#endif // ERRORLIST_H_INCLUDED
