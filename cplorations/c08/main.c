/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] Micah Stalberg
 * [TERM] FALL 2022
 * 
 ****************************************/
#include "symtable.h"
#include "parser.h"
#include "error.h"

int main(int argc, const char *argv[])
{	
    if (argc != 2) {
    // incorrect number of arguments
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);        
    }  

    FILE *fin = fopen( argv[1], "r" );

    if(fin == NULL){ 
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }
    
    parse(fin);
    // symtable_display_table();
    fclose(fin);

}


