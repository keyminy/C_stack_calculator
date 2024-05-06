#pragma once

typedef enum {
	leftparen
	,rightparen
	,plus
	,minus
	,multiply
	,divide
	,eos
	,operand
} words;

double change_value(char* num, int* index);
words classification(char* ch);
double eval(char* postfix);
int priority(char op);
void infix_to_postfix(char* infix, char* postfix);