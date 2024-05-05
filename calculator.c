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
			//스택의 top의 연산자 우선순위와 ch의 우선순위를 비교
			while (!isEmpty(&operator_stk)) {
				if (priority(top(&operator_stk)) >= priority(ch)) {
					//기존의 것 pop
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
			// '(' 도 pop()
			pop(&operator_stk);
			break;
		default:
			// operand
			//printf("%c", ch);
			sprintf_s(post_res, sizeof(post_res), "%s%c", post_res,ch);
			break;
		}
	}
	// stack에 남아있는 operator들을 모조리 pop한다
	while (!isEmpty(&operator_stk)) {
		//printf("%c", pop(&operator_stk));
		sprintf_s(post_res, sizeof(post_res), "%s%c", post_res, pop(&operator_stk));
	}
	return post_res;
}