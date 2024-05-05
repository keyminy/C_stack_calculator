#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "calculator.h"
#include "stack.h"

void add_integer(Tokens* tokens, double val) {
	tokens->integers[tokens->total_tokens] = val;
	tokens->types[tokens->total_tokens] = TOKEN_INTEGER;
	tokens->total_tokens++;
}
void add_char(Tokens* tokens, char ch) {
	tokens->chars[tokens->total_tokens] = ch;
	tokens->types[tokens->total_tokens] = TOKEN_CHAR;
	tokens->total_tokens++;
}

Tokens split_tokens(const char* exp) {
	Tokens tokens = { {0.0},NULL,0,0 };
	double val = 0.0;
	bool valProcessing = false;
	int len = strlen(exp);
	// exp[] = (( 222 + 4 ) * 55 ) - 100 / 7 * 5 - 5 * 10 =
	
	for (int i = 0; i < len; i++) {
		char ch = exp[i];
		if (ch == '=' || ch == ' ' || ch == '\n') {
			continue;
		}
		if (isdigit(ch)) {
			// operand
			//ch - '0' : ���ڿ� ���ڸ� ����ȭ���ش� ex) value = '2' - '0' = 2(integer)
			val = val * 10 + (ch - '0');
			valProcessing = true;
		}
		else {
			// operator
			if (valProcessing) {
				// ���� ������ operand(����)
				add_integer(&tokens, val);
				val = 0;
			}
			valProcessing = false;
			add_char(&tokens, ch);
		}
	}
	// ������ ����ó��
	if (valProcessing) {
		add_integer(&tokens, val);
		val = 0;
	}
	return tokens;
}

// ���� ǥ�� ���� ��� �Լ�
double eval(const Tokens* postfixed_struct) {
	double op1, op2;
	stack stk;
	createStack(&stk);

	for (int i = 0; i < postfixed_struct->total_tokens; i++) {
		if (postfixed_struct->types[i] == TOKEN_INTEGER) {
			double num = postfixed_struct->integers[i];
			//operand�̸�, stack�� push
			push(&stk, num);
		}
		else if (postfixed_struct->types[i] == TOKEN_CHAR) {
			char ch = postfixed_struct->chars[i];
			//operator�̸�, 2���� operand�� pop�� �������� stack�� �ٽ� ����
			op2 = pop(&stk);
			op1 = pop(&stk);
			switch (ch) {
			case '+':
				push(&stk, op1 + op2);
				break;
			case '-':
				push(&stk, op1 - op2);
				break;
			case '*':
				push(&stk, op1 * op2);
				break;
			case '/':
				push(&stk, op1 / op2);
				break;
			}
		}
	}
	return pop(&stk); // ������ ���� ��� ����� return
}
// ū �����ϼ��� �켱���� ����
int priority(char op) {
	switch (op) {
	case '(':
	case ')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return -1;
}



Tokens infix_to_postfix(const Tokens* tokens) {
	stack operator_stk;
	Tokens postfixed_struct = { {0.0},NULL,0,0 };
	createStack(&operator_stk);

	// char* s = "6+(3-2)*4";

	for (int i = 0; i < tokens->total_tokens; i++) {
		if (tokens->types[i] == TOKEN_INTEGER) {
			double num = tokens->integers[i];
			//printf("%d ", num);
			add_integer(&postfixed_struct, num);
		}
		else if (tokens->types[i] == TOKEN_CHAR){
			char ch = tokens->chars[i];
			switch (ch) {
				case '+': case '-': case '*': case '/':
					// operator
					//������ top�� ������ �켱������ ch�� �켱������ ��
					while (!isEmpty(&operator_stk)) {
						if (priority(top(&operator_stk)) >= priority(ch)) {
							//������ �� pop
							//printf("%c",pop(&operator_stk));
							add_char(&postfixed_struct, pop(&operator_stk));
						}
						else {
							break;
						}
					}
					push(&operator_stk, ch);
					break;
				case '(':
					push(&operator_stk, ch);
					break;
				case ')':
					while (top(&operator_stk) != '(') {
						//printf("%c",pop(&operator_stk));
						add_char(&postfixed_struct, pop(&operator_stk));
					}
					// '(' �� pop()
					pop(&operator_stk);
					break;
			}
		}
	}
	// stack�� �����ִ� operator���� ������ pop�Ѵ�
	while (!isEmpty(&operator_stk)) {
		//printf("%c ", pop(&operator_stk));
		add_char(&postfixed_struct, pop(&operator_stk));
	}
	return postfixed_struct;
}