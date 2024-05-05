#pragma once
#define MAX_SIZE 30

typedef enum {
    TOKEN_INTEGER,
    TOKEN_CHAR
} TokenType;

typedef struct {
    double integers[MAX_SIZE];
    char chars[MAX_SIZE];
    TokenType types[MAX_SIZE]; // Array to store type of each token
    int total_tokens; // Total number of tokens
} Tokens;

double eval(const Tokens* postfixed_struct);
int priority(char op);
Tokens infix_to_postfix(const Tokens* tokens);
void add_char(Tokens* tokens, char ch);
void add_integer(Tokens* tokens, double val);
Tokens split_tokens(const char* exp);