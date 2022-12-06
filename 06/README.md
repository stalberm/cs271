### Unit 6 - Hack Assembler

An assembler that translates programs written in Hack assembly language into binary code understood by the Hack hardware platform.

#### Usage

The driver program is contained in `main.c`. 

In order to use it and assemble the Hack code, you simple call `./main [filename]`

`filename` is the name of an assembly file (file with extension `.asm`)

If the assembly file is not in the same directory as the project, then path must be explicitly specifc

Example:

    `./main add/Add.asm`