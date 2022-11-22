/****************************************
 * C-ploration 9 for CS 271
 * 
 * [NAME] Micah Stalberg
 * [TERM] FALL 2022
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include <stdbool.h>




/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	
	char s_new[strlen(s)+1];
	int i = 0;
    char curr_char;
    char next_char;
    for (char *s2 = s; *s2; s2++) {
        curr_char = *s2;
        next_char = *(s2+1);
        if (curr_char == '/' && next_char == '/') {
            break;
        } else if (isspace(*s2)) {
            continue;
        } else {
            s_new[i++] = *s2;
        }
    }
    s_new[i] = '\0';
    strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */

void parse(FILE * file){
	
    instruction instr;
	char line[MAX_LINE_LENGTH] = {0};
    int instr_num = 0;
    unsigned int line_num = 0;
    
    add_predefined_symbols();

    while (fgets(line, sizeof(line), file)) {
        line_num++;

        if (instr_num > MAX_INSTRUCTIONS) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }
        strip(line);
        if (*line == NULL) {
            continue;
        }

        char inst_type = NULL;
        if (is_Atype(line)) {
            if (!parse_A_instruction(line, &instr.a_instruct)){
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.instr_type = A_TYPE;
            inst_type = 'A';
            // instr_num++;
        }
        else if (is_label(line)) {
            inst_type = 'L';
            char *extr_label = malloc(MAX_LABEL_LENGTH);
            extract_label(line, extr_label);
            if (isalpha(extr_label[0]) == 0) {
                exit_program(EXIT_INVALID_LABEL, line_num, extr_label);
            }
            
            if (symtable_find(extr_label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, extr_label);
            }
            symtable_insert(extr_label, instr_num);
            // struct Symbol *result = symtable_find(extr_label);
            // printf("{%s,%d}\n",result->name,result->address);
            // printf("%c  %s\n", inst_type, extr_label);
            continue;
        }
        else if (is_Ctype(line)) {
            inst_type = 'C';
            // instr_num++;
        }

        // printf("%u: %c  %s\n", instr_num, inst_type, line);
        instr_num++;
        
    }
	
}

bool is_Atype(const char *line) {
    return (line[0] == '@');
}

bool is_label(const char *line) {
    return ((line[0] == '(') && (line[strlen(line)-1] == ')'));
}

bool is_Ctype(const char *line) {
    return ((is_Atype(line) != true) && (is_label(line) != true));
}

char *extract_label(const char *line, char* label) {
    int i = 0;
    for (char *s2 = line; *s2; s2++) {
        if ((*s2 == '(') || (*s2 == ')')) {
            continue;
        } else {
            label[i++] = *s2;
        }
    }
    label[i] = '\0';
    return label;
}

void add_predefined_symbols() {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
        predefined_symbol def_sym = predefined_symbols[i];
        symtable_insert(def_sym.name, def_sym.address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
    
    char *s = (char*) malloc(strlen(line));
    strcpy(s, line + 1);
    char *s_end = NULL;

    long result = strtol(s, &s_end, 10);

    if (strcmp(s, s_end) == 0) {
        instr->label = malloc(strlen(line));
        strcpy(instr->label, s);
        instr->address = false;
    } else if (*s_end != 0) {
        return false;
    } else {
        instr->address = result;
        instr->is_addr = true;
    }
    return true;
}