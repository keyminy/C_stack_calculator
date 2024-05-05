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