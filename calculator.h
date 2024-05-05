#pragma once
#define MAX_SIZE 100

typedef struct {
    int integers[MAX_SIZE];
    char chars[MAX_SIZE];
    int num_count;
    int char_count;
} Tokens;

int eval(char exp[]);
int priority(char op);
char* infix_to_postfix(char exp[],char post_res[]);
void add_char(Tokens* tokens, char ch);
void add_integer(Tokens* tokens, int val);
Tokens split_tokens(char exp[]);