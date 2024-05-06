#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "calculator.h"
#include "stack.h"

double change_value(char* num, int* index) {
	// �������� -> ���ڷ�(double)
	double value;
	char temp[100];
	int i,k;
	for (i = 0; num[i] != ' '; i++) {
		temp[i] = num[i];
	}
	temp[i] = '\0';
	value = atof(temp);
	k = *index;
	*index = k + i;
	return value;
}


words classification(char* ch) {
	switch (*ch) {
	case '(':
		return leftparen;
	case ')':
		return rightparen;
	case '+':
		return plus;
	case '-':
		return minus;
	case '*':
		return multiply;
	case '/':
		return divide;
	case '\0':
		return eos;
	default:
		return operand;
	}
}


// ���� ǥ�� ���� ��� �Լ�
double eval(char* postfix) {
	// postfix : 222 4 +55 *100 7 /5 *-5 10 *-
	words temp;
	double op1, op2,value;
	
	stack stk;
	createStack(&stk);
	for (int i = 0; postfix[i] != '\0'; i++) {
		if (postfix[i] == ' ') {
			continue;
		}
		temp = classification(&postfix[i]);
		if (temp == operand) {
			value = change_value(&postfix[i],&i);
			push(&stk, value);
		}
		else {
			op2 = pop(&stk);
			op1 = pop(&stk);
			switch (temp) {
			case plus: push(&stk, op1 + op2); break;
			case minus: push(&stk, op1 - op2); break;
			case multiply: push(&stk, op1 * op2); break;
			case divide: push(&stk, op1 / op2); break;
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