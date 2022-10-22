// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.
//Initialize product to 0
@2
M=0

//If r0 is 0, product r2 will still be 0
@0
D=M
@END
D;JEQ

//If r1 is 0, product r2 will still be 0
@1
D=M
@END
D;JEQ

//Get a counter variable in RAM3 equal to our second value
//So we will add r0 to our product r1 times
@1
D=M
@3
M=D

(LOOP)
//Get r0
@0
D=M

//Add r0 to the product
@2
M=M+D

//Decrement our counter
@3
M=M-1

//If our counter variable is greater than 0 keep looping
D=M
@LOOP
D;JGT

(END)
@END
0;JMP