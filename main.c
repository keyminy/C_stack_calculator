#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // for isdigit function
#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include "calculator.h"

int main()
{
    stack stk; //구조체 변수 선언(스택 생성) 
    createStack(&stk);

	char szBuffer[50] = { 0 };
	Tokens tokenized;
	// input :  (( 222 + 4 ) * 55 ) - 100 / 7 * 5 - 5 * 10 =
	// 혹은 6+(3-2)*4
	fgets(szBuffer, sizeof(szBuffer), stdin);
	tokenized = split_tokens(szBuffer);
	
	Tokens postfixed_struct;
	postfixed_struct = infix_to_postfix(&tokenized);

	printf("결과 : %f\n", eval(&postfixed_struct));
    return 0;
}