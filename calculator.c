#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
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
			push(&stk, value);
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

void infix_to_postfix(char* infix, char* postfix) {
	stack stk;
	createStack(&stk);
	// char* s = "10+(3-2)*4";
	
	char* src = infix;
	char* dest = postfix;

	while (*src != '\0') {
		if (isdigit(*src)) {
			// �����̸�
			while (isdigit(*src)) {
				*dest++ = *src++;
			}
			// operator�� ������ 
			/* ������ ������ ���� �߿��մϴ�(���ڸ� �� �̻� ����)
			 postfix -> 3 5 189 * + */
			*dest++ = ' ';
		}
		// ��������, Ȯ���� operator
		else if (*src == '(') {
			push(&stk, *src++);
		}
		else if (*src == ')') {
			while (top(&stk) != '(') {
				*dest++ = pop(&stk);
			}
			// '(' ����
			pop(&stk);
			src++;
		}
		else if (*src == '+' || *src == '-' || *src == '/' || *src == '*') {
			while (!isEmpty(&stk)) {
				if (priority(top(&stk)) >= priority(*src)) {
					//stack�� �ִ°� ���� dest�� �ִ� �۾�
					*dest++ = pop(&stk);
				}
				else {
					break;
				}
			}
			push(&stk, *src++);
		}
		else {
			src++;
		}
	}
	//stack�� ���� �ִ� ������ dest�� �߰�
	while (!isEmpty(&stk)) {
		*dest++ = pop(&stk);
	}
	*dest = '\0';
}