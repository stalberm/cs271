// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(START)
@SCREEN
//Capture screen location in D
D=A
@R0
//Store screen location in RAM[0]
M=D

//256 rows of 32 16 bit words - 256x32 = 8192
//SCREEN starts at 16384 and KBD starts at 24576 - 8192 from SCREEN to KBD
//Store the number of fills needed for the screen in RAM[1]
@8192
D=A
@R1
M=D

//Get keyboard input, fillwhite if 0, else fill black
(INPUT)
@KBD
D=M
@FILLWHITE
D;JEQ
@FILLBLACK
D;JGT

//Infinite loop to check for KBD input
@INPUT
0;JMP


(FILLWHITE)
D=0
//Get current screen address out of RAM[0]
@R0
A=M
//Set the value of that address to 0 - white
M=D
//Filled another piece, so update current screen address to current val plus 1
@R0
M=M+1

//A piece was filled, so decrement our counter 
@R1
M=M-1
D=M

//If the counter is 0, we filled the screen so repeat if not filled
@FILLWHITE
D;JGT

@START
0;JMP

(FILLBLACK)
D=-1
//Get current screen address out of RAM[0]
@R0
A=M
//Set the value of that address to -1 - black
M=D
//Filled another piece, so update current screen address to current val plus 1
@R0
M=M+1

//A piece was filled, so decrement our counter 
@R1
M=M-1
D=M
//If the counter is 0, we filled the screen so repeat if not filled
@FILLBLACK
D;JGT

@START
0;JMP