/* instruction_list.h - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains data structure definition and
   function prototypes for the instruction list

*/


#ifndef INSTRUCTION_LIST_H_INCLUDED
#define INSTRUCTION_LIST_H_INCLUDED

/************* Includes ****************/
#include "p4.h"

/**************Data structures ****************/

/* this node will hold an instruction read
from the assembly file to later be converted
into a hex code */
typedef struct instnode_s
{
    /* variables all instructions will utilize */
    int  address;                 /* numeric address of instruction as integer */
    int lineno;                   /* line number the instruction was read from */
    char label[LABEL_LEN];        /* name of label if one exists */
    int  inst_type;               /* type of instruction: R, I, J */
    char opcode_name[OPCODE_LEN]; /* name of the opcode */
    char opcode_bin[OPCODE_LEN];  /* binary string for opcode */
    char bin_inst[INST_LEN];      /* binary represenation of compiled instruction */
    char hex_inst[INST_LEN];      /* hex representation of compiled instruction */

    /* type dependent variables */
    char rs1[REG_LEN];       /* Register source 1 */
    char rs2[REG_LEN];       /* Register source 2 */
    char rt[REG_LEN];        /* Register target   */
    char sa[REG_LEN];        /* shift amount      */
    char imm[IMMEDIATE_LEN]; /* immediate address */
    char symbol[LABEL_LEN];  /* symbol */

    struct instnode_s *next; /* pointer to next node in list */

} instnode;

typedef struct instlist_s
{
    instnode *head;  /* pointer to the head of the list */
    instnode *cur;   /* node pointer used for traversal */

    int count;       /* number of instructions */

} instlist;


/*************** Functions **************************************/

/* add a node to list */
void add_node(instlist *list, instnode *node);

/* delete the list */
void delete_list(instlist* list);


#endif // INSTRUCTION_LIST_H_INCLUDED
