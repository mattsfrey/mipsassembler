/* dataentry.h - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains data structure definition and
   function prototypes for the data entry list

*/


#ifndef DATAENTRY_H_INCLUDED
#define DATAENTRY_H_INCLUDED


/********* Includes *****************/
#include "p4.h"

/*************** Data structures *********************/

/* this node will hold a data entry
   from the data section of the asm file */
typedef struct datanode_s
{
    /* variables */
    int address;                  /* numeric address of instruction as integer */
    int lineno;                   /* line number the instruction was read from */
    char label[LABEL_LEN];        /* name of label if one exists */

    char binval[INST_LEN];      /* binary represenation of compiled instruction */
    char hex_val[INST_LEN];      /* hex representation of compiled instruction */

    struct datanode_s *next;

} datanode;

typedef struct datalist_s
{
    datanode *head;  /* pointer to the head of the list */
    datanode *cur;   /* node pointer used for traversal */

    int count;       /* number of instructions */

} datalist;


/*************** Functions **************************************/

/* add a node to list */
void add_datanode(datalist *list, datanode *node);

/* delete the list */
void delete_datalist(datalist* list);



#endif // DATAENTRY_H_INCLUDED
