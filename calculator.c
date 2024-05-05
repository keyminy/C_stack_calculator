#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#include "stack.h"

// ���� ǥ�� ���� ��� �Լ�
int eval(char exp[]) {
	int op1, op2, value;
	int len = strlen(exp);
	char ch;
	stack stk;
	createStack(&stk);
	// char exp[] = "632-4*+";
	for (int i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '*' && ch != '/' && ch != '+' && ch != '-') {
			//operand�̸�, stack�� push
			//���ڿ� ���ڸ� ����ȭ���ش� ex) value = '2' - '0' = 2(integer)
			value = ch - '0';
			push(&stk,value);
		}
		else {
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

char* infix_to_postfix(char exp[],char post_res[]) {
	char ch;
	int len = strlen(exp);
	stack operator_stk;
	createStack(&operator_stk);
	// char* s = "6+(3-2)*4";
	for (int i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/':
			// operator
			//������ top�� ������ �켱������ ch�� �켱������ ��
			while (!isEmpty(&operator_stk)) {
				if (priority(top(&operator_stk)) >= priority(ch)) {
					//������ �� pop
					//printf("%c",pop(&operator_stk));
					sprintf_s(post_res, sizeof(post_res),"%s%c",post_res,pop(&operator_stk));
				}
				else {
					break;
				}
			}
			push(&operator_stk, ch);
			break;
		case '(':
			push(&operator_stk,ch);
			break;
		case ')':
			while (top(&operator_stk) != '(') {
				//printf("%c",pop(&operator_stk));
				sprintf_s(post_res, sizeof(post_res), "%s%c", post_res, pop(&operator_stk));
			}
			// '(' �� pop()
			pop(&operator_stk);
			break;
		default:
			// operand
			//printf("%c", ch);
			sprintf_s(post_res, sizeof(post_res), "%s%c", post_res,ch);
			break;
		}
	}
	// stack�� �����ִ� operator���� ������ pop�Ѵ�
	while (!isEmpty(&operator_stk)) {
		//printf("%c", pop(&operator_stk));
		sprintf_s(post_res, sizeof(post_res), "%s%c", post_res, pop(&operator_stk));
	}
	return post_res;
}