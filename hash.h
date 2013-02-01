/* hash.h - Matthew Frey -MF969948 - csi 402 - 4/13/11

   this file contains data structure definitions and
   functions prototypes for use with the hash table.
*/



#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED


/************* Includes **************/
#include "p4.h"

/************** Constants *************/
#define HASH_SIZE 13


/* Data structures =====================================================
 * *****************************************************************
 * This program makes use of a hash table with separate chaining
 * for each key. The index of the table is a linked list itself
 * comprised of 'TableNode's, each tablenode has a head pointer to a
 * linked list of 'ListNode's
 *******************************************************************/

/* ListNode - contains each value in the table to be stored under a
 * specific tablenode marked with a unique key. has a next pointer to
 * traverse to the next node in the list, as well as a string holding
 * the entries value
 */
typedef struct ListNode
{
	struct ListNode* next;   /* pointer to next node */
	char value[LINE_LEN];     /* value of entry */
	int address;             /* integer address to location */
} lnode;

/* TableNode - each table node serves as an index in the hash table,
 * it has an integer value for the key it represents, as well as an
 * integer to hold the number of entries stored at this particular index.
 * the head pointer points to the first list entry under this index.
 */
typedef struct TableNode
{
    struct TableNode* next; //pointer to next node in table
    lnode*     head;        //pointer to first entry in entry list
    int key;                //string value held by node
    int entries;            //number of entries at this key
} tnode;
/*====================================================================*/

//function prototypes
tnode* addhashnode(tnode* head, int key, const char* val, int address);
void deletetable(tnode* head);

/* returns true if hash key and value are found, false otherwise */
int checkHash(tnode* head, int key,const char* val, int *address);

/* generate hash and return key*/
int hashgen(char *s,  int T);



#endif // HASH_H_INCLUDED
