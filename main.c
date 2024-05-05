#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // for isdigit function
#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"
#include "calculator.h"

void removeNewLine(char* szBuffer);

int main()
{
    stack stk; //구조체 변수 선언(스택 생성) 
    createStack(&stk);

	char szBuffer[50] = { 0 };
	Tokens tokenized;
	// input :  (( 222 + 4 ) * 55 ) - 100 / 7 * 5 - 5 * 10 =
	fgets(szBuffer, sizeof(szBuffer), stdin);
	tokenized = split_tokens(szBuffer);
	
	printf("tokenized : %s\n", tokenized.chars);
	for (int i = 0; i < tokenized.num_count; i++) {
		printf("숫자 : %d\n", tokenized.integers[i]);
	}

	char* s = "100*4";
	char post_res[MAX_SIZE] = { NULL };
	printf("중위표시 수식 : %s\n", s);
	printf("후위 표시 수식 : %s\n", infix_to_postfix(s,post_res));
	printf("결과 : %d\n", eval(post_res));

    return 0;
}

void removeNewLine(char* szBuffer) {
	int len = strlen(szBuffer);
	if (len > 0 && szBuffer[len - 1] == '\n') {
		szBuffer[len - 1] = '\0';
	}
}