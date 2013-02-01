#Test case 1 for assembler. 

               .text
test1:         lwa    $1,val1      #Puts -1 in $1.
               prh    $1

val12:         lwa    $2,val2
               prh    $2
               sll    $3,$2,16
               prh    $3

val123:        srl    $4,$1,16
               prh    $4

val1234:       sra    $5,$1,16
               prh    $5

#A label with 8 characters.
val12345:      xor    $6,$1,$2
               prh    $6
               lwb    $7,0($1)
               prh    $7
               hlt

               .data
val1:          .word  -1:4
val2:          .word  65535:1

#No more lines.
