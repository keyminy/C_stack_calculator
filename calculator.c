#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#include "stack.h"

// 후위 표기 수식 계산 함수
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
			//operand이면, stack에 push
			//문자열 숫자를 정수화해준다 ex) value = '2' - '0' = 2(integer)
			value = ch - '0';
			push(&stk,value);
		}
		else {
			//operator이면, 2개의 operand를 pop후 연산결과를 stack에 다시 넣음
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
	return pop(&stk); // 마지막 최종 계산 결과를 return
}