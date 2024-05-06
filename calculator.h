#pragma once
#define MAX_SIZE 100

int eval(char exp[]);
int priority(char op);
void infix_to_postfix(char* infix, char* postfix);