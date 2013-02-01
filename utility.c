/* utility.c - Matthew Frey -MF969948 - csi 402 - 4/13/11

   this file contains utility functions to aid in
   the main method of p4. Mostly converting between
   number formats.

*/


/********** Includes ****************/
#include "p4.h"

/*************** functions *****************/

/* takes in line, returns 0 or 1 if there
   is a comment in the line or not */
int commentExists(const char *line)
{
    /* return value */
    int ret = 0;

    /* check for # in line */
    if (strchr(line, '#'))
    {
        ret = 1;
    }

    return ret;
}

/* checks if a line is blank */
int isBlank(const char *line)
{
    int i = 0; /* iterator */

    while (i < strlen(line))
    {
        /* check for symbol other than whitespace */
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
        {
            /* found a non whitespace symbol, return o */
            return 0;
        }
        /* increment iterator */
        i++;
    }
    /* found nothing but whitespace, return true */
    return 1;
}

/* takes in a line, returns 1 if
 the first non-whitespace character is a comment */
int isComment(const char *line)
{

    int i = 0;    /* iterator */

    /* loop through line, if we encounter something
       other than a tab or whitespace before a #, the line
       is not a comment, otherwise it is */
    while(i < strlen(line))
    {
        if (line[i] != '#')
        {
            if (line[i] != '\t' && line[i] != ' ')
            {
                /* first char was not a #, return false */
                return 0;
            }
        }
        else
        {
            /* first char other than whitespace was a #, return true */
            return 1;
        }
        i++;
    }
    return 0;
}

/*takes in a line, will strip out the comment behind it */
void stripComment(char *line)
{
    int i;   /* iterator */

    /* set iterator to last character  in line */
    i = strlen(line)-1;

    while (i >= 0)
    {
        if (line[i] == '#')
        {
            line[i] = '\0';
        }
        i--;
    }

}

/* takes in a char pointer, will trim the whitespace
  characters from the front and end of the string ,
  returning the new trimmed string */
char *trimWhiteSpace(char *str)
{
    char *end;

    /* trim leading space */
    while(isspace(*str))
    {
        str++;
    }
    if(*str == 0)
    {
        /* string was all spaces */
        return str;
    }

    /* trim trailing space */
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end))
    {
        end--;
    }
    /* write new null terminator */
    *(end+1) = 0;

    /* return trimmed string */
    return str;
}

/* takes in a string holding a register in format $NUM
   and returns a string of 5 bit binary */
char* regToBin(char *reg)
{
    int dec = 0;  /* decimal number */
    char bin[REGBITS] = "00000";
    char integer[OPCODE_LEN];
    int i, j=0;

    /* strip otu the $ symbol */
    for(i=0; i<=strlen(reg); i++)
    {
        if (reg[i] != '$')
        {
            integer[j] = reg[i];
            j++;
        }
    }

    /* conver to int */
    dec = atoi(integer);

    /* computer binary and fill the string */
    i = strlen(bin)-1;
    while (dec > 0)
    {
        bin[i] = (char)(((int)'0')+(dec % 2));
        dec /= 2;
        i--;
    }

    strcpy(reg, bin);

    /* return binary string */
    return reg;
}

/* return a binary string for immediate number */
char* immToBin(char *imm)
{
    int dec = 0;  /* decimal number */
    int negflag = 0;
    char bin[IMMEDIATE_LEN] = "0000000000000000";
    int i;
    int carry = 0;

    dec = atoi(imm);

    /* check if negative and set flag if so */
    if (dec < 0)
    {
        dec = -dec;
        negflag = 1;
    }

    /* computer binary and fill the string */
    i = strlen(bin)-1;
    while (dec > 0)
    {
        bin[i] = (char)(((int)'0')+(dec % 2));
        dec /= 2;
        i--;
    }

    /* convert to two's complement if negative */
    if (negflag)
    {
        /* negate the bits */
        for (i = 0; i<strlen(bin); i++)
        {
            if (bin[i] == '1')
            {
                bin[i] = '0';
            }
            else if (bin[i] == '0')
            {
                bin[i] = '1';
            }
        }
        /* add 1 */
        i = strlen(bin)-1;
        carry = 1;
        while (i > 0)
        {
            if (carry == 1)
            {
                if (bin[i] == '0')
                {
                    bin[i] = '1';
                    carry = 0;
                }
                else
                {
                    bin[i] = '0';
                    carry = 1;
                }
            }
            i--;
        }
    }
    strcpy(imm, bin);

    /* return binary string */
    return imm;
}

/* takes in a string representing an integer and
   will convert it to a 32 bit binary string */
char* numTo32Bin(char *num)
{
    int dec = 0;  /* decimal number */
    int negflag = 0;
    char bin[INST_LEN] = "00000000000000000000000000000000";
    int i;
    int carry = 0;

    dec = atoi(num);

    /* set flag if negative */
    if (dec < 0)
    {
        dec = -dec;
        negflag = 1;
    }

    /* computer binary and fill the string */
    i = strlen(bin)-1;
    while (dec > 0)
    {
        bin[i] = (char)(((int)'0')+(dec % 2));
        dec /= 2;
        i--;
    }

    /* convert to two's complement if negative */
    if (negflag)
    {
        /* negate the bits */
        for (i = 0; i<strlen(bin); i++)
        {
            if (bin[i] == '1')
            {
                bin[i] = '0';
            }
            else if (bin[i] == '0')
            {
                bin[i] = '1';
            }
        }
        /* add 1 */
        i = strlen(bin)-1;
        carry = 1;
        while (i > 0)
        {
            if (carry == 1)
            {
                if (bin[i] == '0')
                {
                    bin[i] = '1';
                    carry = 0;
                }
                else
                {
                    bin[i] = '0';
                    carry = 1;
                }
            }
            i--;
        }
    }
    strcpy(num, bin);

    /* return 32 bit binary string */
    return num;
}

/* i had to write this function because ITSUNIX doesn't support
   it. takes in a string and a limiting size, returns the strlen
   of the string if its less than or equal to the limit, otherwise
   it returns the limit */
size_t strnlen(const char *s, size_t n)
{
    if (strlen(s) <= n)
    {
        return strlen(s);
    }
    else
    {
        return n;
    }
}

/* another function that ITSUNIX doesnt support. this function
   allocates a new string from a subset of an existing one,
   is used to facilitate the strsub below */
char* strndup (char const *s, size_t n)
{
    size_t len = strnlen (s, n);
    char *new = malloc (len + 1);

    if (new == NULL)
        return NULL;

    new[len] = '\0';
    return memcpy (new, s, len);
}

/* this function allows for taking a subset of a string,
   which is useful for the binary to hex conversions. it takes
   in a string, a start position and length to copy, and
   will copy a new string in that range and return the char
   pointer to it */
char* substring(const char* str, size_t begin, size_t len)
{
    /* check for problems with string size and position variables */
    if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
        return 0;

    /* return pointer to new string */
    return strndup(str + begin, len);
}

/* this function will take in a binary number and convert it to
   hexidecimal string of 32 bits */
char* binToHex32(char *bin)
{
    int i=0; /* iterator */
    char hex[INST_LEN];  /* hex string holder */
    char *sub;           /* string ptr for use with strsub */

    /* clear out hex string */
    strcpy(hex, "");

    /* loop through whole binary string, 32 bits */
    while (i < LABEL_LEN)
    {
        /* grab 4 digits of the binary */
        sub = substring(bin, i, 4);

        /* compare to dif binary strings and concatenate the correct hex
          digit to the hex string */
        if (strcmp(sub, "0000")==0)
        {
            strcat(hex, "0");
        }
        else if (strcmp(sub, "0001")==0)
        {
            strcat(hex, "1");
        }
        else if (strcmp(sub, "0010")==0)
        {
            strcat(hex, "2");
        }
        else if (strcmp(sub, "0011")==0)
        {
            strcat(hex, "3");
        }
        else if (strcmp(sub, "0100")==0)
        {
            strcat(hex, "4");
        }
        else if (strcmp(sub, "0101")==0)
        {
            strcat(hex, "5");
        }
        else if (strcmp(sub, "0110")==0)
        {
            strcat(hex, "6");
        }
        else if (strcmp(sub, "0111")==0)
        {
            strcat(hex, "7");
        }
        else if (strcmp(sub, "1000")==0)
        {
            strcat(hex, "8");
        }
        else if (strcmp(sub, "1001")==0)
        {
            strcat(hex, "9");
        }
        else if (strcmp(sub, "1010")==0)
        {
            strcat(hex, "A");
        }
        else if (strcmp(sub, "1011")==0)
        {
            strcat(hex, "B");
        }
        else if (strcmp(sub, "1100")==0)
        {
            strcat(hex, "C");
        }
        else if (strcmp(sub, "1101")==0)
        {
            strcat(hex, "D");
        }
        else if (strcmp(sub, "1110")==0)
        {
            strcat(hex, "E");
        }
        else if (strcmp(sub, "1111")==0)
        {
            strcat(hex, "F");
        }

        /* free memory used by strsub */
        free(sub);

        /* increment iterator to next block of binary digits */
        i += 4;
    }

    /* copy hex string to return ptr */
    strcpy(bin, hex);

    /* return new string */
    return bin;

}

/* this function is used to take an integer address
   and convert it into a 16 bit hex string */
char* addrToHex(int address, char *ret)
{
    char bin[IMMEDIATE_LEN] = "0000000000000000";
    int i;
    char hex[IMMEDIATE_LEN];
    char *sub;
    int dec = address;

    /* computer binary and fill the string */
    i = strlen(bin)-1;
    while (dec > 0)
    {
        bin[i] = (char)(((int)'0')+(dec % 2));
        dec /= 2;
        i--;
    }

    strcpy(hex, "");
    i = 0;

    /* loop through blocks of 4 binary digits and
       concatenate the correct hex symbol to the hex string */
    while (i < IMMEDIATE_LEN-1)
    {
        /* grab next block */
        sub = substring(bin, i, 4);
        if (strcmp(sub, "0000")==0)
        {
            strcat(hex, "0");
        }
        else if (strcmp(sub, "0001")==0)
        {
            strcat(hex, "1");
        }
        else if (strcmp(sub, "0010")==0)
        {
            strcat(hex, "2");
        }
        else if (strcmp(sub, "0011")==0)
        {
            strcat(hex, "3");
        }
        else if (strcmp(sub, "0100")==0)
        {
            strcat(hex, "4");
        }
        else if (strcmp(sub, "0101")==0)
        {
            strcat(hex, "5");
        }
        else if (strcmp(sub, "0110")==0)
        {
            strcat(hex, "6");
        }
        else if (strcmp(sub, "0111")==0)
        {
            strcat(hex, "7");
        }
        else if (strcmp(sub, "1000")==0)
        {
            strcat(hex, "8");
        }
        else if (strcmp(sub, "1001")==0)
        {
            strcat(hex, "9");
        }
        else if (strcmp(sub, "1010")==0)
        {
            strcat(hex, "A");
        }
        else if (strcmp(sub, "1011")==0)
        {
            strcat(hex, "B");
        }
        else if (strcmp(sub, "1100")==0)
        {
            strcat(hex, "C");
        }
        else if (strcmp(sub, "1101")==0)
        {
            strcat(hex, "D");
        }
        else if (strcmp(sub, "1110")==0)
        {
            strcat(hex, "E");
        }
        else if (strcmp(sub, "1111")==0)
        {
            strcat(hex, "F");
        }

        /* free memory used by strsub */
        free(sub);

        /* jump to next block of 4 binary digits */
        i += 4;
    }

    /* copy hex string to return ptr */
    strcpy(ret, hex);

    /* return new string */
    return ret;
}
