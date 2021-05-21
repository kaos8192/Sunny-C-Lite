#ifndef SCANNER_H
#define SCANNER_H

#define ERROR 0

#define TOK_INT 1
#define TOK_PLUS 2
#define TOK_MINUS 3
#define TOK_TIMES 4
#define TOK_DIV 5
#define TOK_MOD 6
#define TOK_LPAREN 7
#define TOK_RPAREN 8

#define END_OF_STRING 9

typedef struct Token {
   int tok_id; //required
   int value; //optional
} Token; 

void initialize_state(char* input);
Token next_token();
void print_token(Token t);
#endif
