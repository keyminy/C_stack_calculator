#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
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
			push(&stk, value);
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
// 큰 숫자일수록 우선순위 높음
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
			// 숫자이면
			while (isdigit(*src)) {
				*dest++ = *src++;
			}
			// operator가 나오면 
			/* 공백의 역할은 아주 중요합니다(두자리 수 이상 연산)
			 postfix -> 3 5 189 * + */
			*dest++ = ' ';
		}
		// 이제부터, 확실한 operator
		else if (*src == '(') {
			push(&stk, *src++);
		}
		else if (*src == ')') {
			while (top(&stk) != '(') {
				*dest++ = pop(&stk);
			}
			// '(' 제거
			pop(&stk);
			src++;
		}
		else if (*src == '+' || *src == '-' || *src == '/' || *src == '*') {
			while (!isEmpty(&stk)) {
				if (priority(top(&stk)) >= priority(*src)) {
					//stack에 있는거 빼서 dest에 넣는 작업
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
	//stack에 남아 있는 값들을 dest에 추가
	while (!isEmpty(&stk)) {
		*dest++ = pop(&stk);
	}
	*dest = '\0';
}