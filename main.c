#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#include "stack.h"

void removeNewLine(char* szBuffer);

int main()
{
    stack stk; //구조체 변수 선언(스택 생성) 
    createStack(&stk);

	char szBuffer[50] = { 0 };

	fgets(szBuffer, sizeof(szBuffer), stdin);
	// input :  ( ( 222 + 4 ) * 55 ) - 100 / 7 * 5 - 5 * 10 =
	removeNewLine(szBuffer);
	char* str2 = NULL;
	char* p_splited = strtok_s(szBuffer, " ",&str2);

	while (p_splited != NULL) {
		printf("%s\n", p_splited);
		p_splited = strtok_s(NULL," ",&str2);
	}

    return 0;
}

void removeNewLine(char* szBuffer) {
	int len = strlen(szBuffer);
	if (len > 0 && szBuffer[len - 1] == '\n') {
		szBuffer[len - 1] = '\0';
	}
}