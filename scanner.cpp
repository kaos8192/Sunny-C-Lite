#include "scanner.h"

char* in_string;
char* current_position;

void initialize_state(char* input)
{
	in_string = current_position = input;
}

Token next_token()
{
	Token tok;
	tok.value = 0;
	char ch = *current_position;

	if(ch >= '0' && ch <= '9'){
		tok.tok_id = 1;
		tok.value = 0;
		while(ch >= '0' && ch <= '9'){
			tok.value *= 10;
			tok.value += ch - '0';
			++current_position;
			ch = *current_position;
		}
	}else if(*current_position == '+'){
		tok.tok_id = 2;	
	}else if(*current_position == '-'){
		tok.tok_id = 3;
	}else if(*current_position == '*'){
		tok.tok_id = 4;
	}else if(*current_position == '/'){
		tok.tok_id = 5;
	}else if(*current_position == '%'){
		tok.tok_id = 6;
	}else if(*current_position == '('){
		tok.tok_id = 7;
	}else if(*current_position == ')'){
		tok.tok_id = 8;
	}else if (!current_position || *current_position == '\0') {
		tok.tok_id = END_OF_STRING;
		return tok;
	}else{
		tok.tok_id = ERROR;
	}

	++current_position;
	return tok;
}
