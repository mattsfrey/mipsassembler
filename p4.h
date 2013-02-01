/* p4.h - Matthew Frey - MF969948 - csi 402 - 4/13/11

   this file contains the prototypes for the
   utility functions as well as many of the constants used
   throughout the program.

*/


#ifndef P4_H_INCLUDED
#define P4_H_INCLUDED

/************* Includes **************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/*************** constants ******************/

/*lengths of different arrays */
#define OPCODE_LEN 8
#define LABEL_LEN 32
#define INST_LEN 33
#define REG_LEN 6
#define IMMEDIATE_LEN 17
#define LINE_LEN 81
#define FILE_LEN 255


/* types of instructions */
#define RTYPE 0
#define ITYPE 1
#define JTYPE 2


#define REGBITS 6 /* register string length */


/* utility functions */


/* checks if a line is blank */
int isBlank(const char *line);

/* check for comment in line */
int commentExists(const char *line);

/* is line a comment ? */
int isComment(const char *line);

/* strips inline comment out of instruction */
void stripComment(char *line);

/* trim whitespace from string */
char *trimWhiteSpace(char *str);

/* return binary string for reg number */
char* regToBin(char *reg);

/* return a binary string for immediate number */
char* immToBin(char *imm);

/* converts an integer in string format to a 32 bit binary string */
char* numTo32Bin(char *num);

/* returns a pointer to a new strign subset */
char* substring(const char* str, size_t begin, size_t len);

/* converts a 32 bit binary string to hex */
char* binToHex32(char *bin);

/* takes in an integer address and converts it to a 16 bit hex string */
char* addrToHex(int address, char *ret);


#endif // P4_H_INCLUDED
