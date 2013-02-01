           .text
#Factorial function.

fact:      li      $5,1      #$5 -- counter.
           move    $6,$5     #$6 -- result.

comp:      jeq     $5,$1,factpr
           addi    $5,$5,1
           mul     $6,$6,$5
           j       comp

factpr:    prr     $6
           jr      $31

#Fibonacci function.

fibo:      move    $10,$0
           addi    $11,$10,1
           li      $12,1

loop:      add     $13,$10,$11
           addi    $12,$12,1
           jeq     $12,$1,fibpr   #We can print result.
           move    $10,$11
           move    $11,$13
           j       loop

fibpr:     prr     $13
           jr      $31
