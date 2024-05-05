#pragma once
int eval(char exp[]);
int priority(char op);
char* infix_to_postfix(char exp[],char post_res[]);