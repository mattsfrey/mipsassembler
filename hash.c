/* Program 4 - 4/13/2011
 * Matthew Frey - MF969948
 *
 * This source file defines the hash functions used in p4.c
 *
 */


/***************** Includes ***********************/
#include "hash.h"


/******************* Functions ******************/

int hashgen(char *s,  int T) {

   /* The parameter s represents the symbol to be hashed and  */
   /* the parameter T represents the size of the hash table.  */
   /* The function returns the hash value for the symbol s.   */

   /* String s is assumed to be terminated with '\0'.         */
   /* It is also assumed that T is at least 2. The returned   */
   /* hash value is an integer in the range 0 to T-1.         */

   /* The function computes the hash value using arithmetic   */
   /* based on powers of the BASE value defined below.        */

   #define  BASE   127

   int h = 0;     /* Will hold the hash value at the end. */
   int temp;      /* Temporary.                           */

   /* The hash value is computed in the for loop below. */
   for (;  *s != 0;  s++) {
       temp = (BASE * h + *s);
       if (temp < 0) temp = -temp;
       h = temp % T;
   }

   /* The hash value computation is complete. So, */
   return h;

} /* End of hash_example_one */


/* addhashnode - this function will take an entry denoted by key and value,
 * and place it into the table appropriately. It will first look to see
 * if a table index has been created for the given key and add the entry
 * to that index. If the table is empty or there is no such index, a
 * new table node will be created and the entry attached to that.
 * A pointer to the head node is returned.
 */
tnode* addhashnode(tnode* head, int key, const char* val, int address)
{
	tnode* cur  = NULL; //used for traversing the table
	lnode* lcur = NULL; //used for traversing the lists

	/* Case 1 - no nodes in table yet
	 * -create new table node and make that the head
	 * -create new listnode and add as an entry
	 */
	if (head == NULL)
	{
		//allocate new node for head
		head = malloc(sizeof(tnode));

		//copy key to new node
		head->key = key;

		//allocate new node for the first entry under this index
		head->head = malloc(sizeof(lnode));

		//copy the value to the new entry
		strcpy(head->head->value, val);

		//copy address to the new entry
		head->head->address = address;

		//set the new entry nodes' next ptr to null
		head->head->next = NULL;

		//set number of entries for this index to 1
		head->entries = 1;

		//set the next ptr for this index node to null
		head->next = NULL;

		//return new head value
		return head;
	}
	/* Case 2 - head node defined, search for matching key
	 * -if matching key found, add new entry
	 * -if no matching key found, create new table and then add entry
	 */
	cur = head;
	while (cur != NULL)
	{
		if (cur->key == key)
		{
			//got match, loop to end of list and append new entry node
			lcur = cur->head;
			while (lcur->next != NULL)
				lcur = lcur->next;

			//allocate new entry node
			lcur->next = malloc(sizeof(lnode));

			//copy value to new node
			strcpy(lcur->next->value, val);

			//copy address to the new entry
            lcur->next->address = address;


			//set new nodes next ptr to null
			lcur->next->next = NULL;

			//increment number of entries for this index
			cur->entries++;

			//return head ptr
			return head;
		}
		//reached end of list
		//add node onto end of table and then add new entry
		if (cur->next == NULL)
		{
			//allocate new table node
			cur->next = malloc(sizeof(tnode));

			//set table nodes key
			cur->next->key = key;

			//allocate new entry node
			cur->next->head = malloc(sizeof(lnode));

			//set new entry node's next ptr to null
			cur->next->head->next = NULL;

			//copy the value to the new entry
			strcpy(cur->next->head->value, val);

			cur->next->head->address = address;

			//set new table's entry variable to 1
			cur->next->entries=1;

			//set new nodes next to null
			cur->next->next = NULL;

			//exit loop
			cur = NULL;
		}
		else
		{
			//traverse to next node
			cur=cur->next;
		}
	}
	//return ptr to head
	return head;
}

/* this function takes in a head pointer, a key, a value, and a pointer
  to return the address found into if such a hash is found */
int checkHash(tnode* head, int key,const char* val, int *address)
{
    /* temp nodes for traversal */
    tnode* tcur = NULL;
    lnode* lcur = NULL;

    /* set traversal node to head of list */
    tcur = head;

    /* loop through looking for desired key */
    while (tcur != NULL)
    {
        if (tcur->key == key)
        {
            /* found key, loop through looking for matching value */
            lcur = tcur->head;
            while (lcur != NULL)
            {
                if (strcmp(lcur->value, val)==0)
                {
                    /* found matching vlaue, set the address and return true */
                    *address = lcur->address;
                    return 1;
                }
                /* traverse to next node */
                lcur = lcur->next;
            }
        }
        /* traverse to next node */
        tcur = tcur->next;
    }

    /* matching key and vlaue were not found, return false */
    return 0;
}


/* deletetable - clean up function that will traverse through the table
 * deleting all entries
 */
void deletetable(tnode* head)
{
	//node ptrs used for place holders / traversing
	tnode* tcur  = NULL;
	tnode* tcur2 = NULL;
	lnode* lcur  = NULL;
	lnode* lcur2 = NULL;

	//exit if table is empty
	if (head == NULL)
		return;

	//loop through table
	tcur = head;
	while (tcur != NULL)
	{
		//loop through entry list
		lcur = tcur->head;
		while (lcur != NULL)
		{
			//delete each entry
			lcur2 = lcur;
			lcur = lcur->next;
			free(lcur2);
		}
		//delete each index
		tcur2 = tcur;
		tcur = tcur->next;
		free(tcur2);
	}
}
