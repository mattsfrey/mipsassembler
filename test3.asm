#Test case 2 for assembler. (Contains several syntax errors.)

               .text
               lwa    $1,val1      
               prh    $1
               j      test0        
               lwa    $2,val2      
val12:         prh    $2
               sll    $3,$2,16
               prh    $5

val12:         srl    $4,$1,16     
               prh    $4

valxxxxx:      sra    $5,$1,3     
               prh    $5

#Uses xor opcode.
val2345:       xor    $6,$1,$2
               prhh   $6           
               lwb    $30,0($1)
               prh    $7
               hlx

               .data
val1:          .word  -1:4
test1:         .resw   15          
val1:          .word  65535:1
