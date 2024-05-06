#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "calculator.h"

int main()
{
	stack stk; //����ü ���� ����(���� ����) 
	createStack(&stk);

	char szBuffer[50] = { 0 };
	char postfix[50] = { 0 };

	fgets(szBuffer, sizeof(szBuffer), stdin);
	// input :  (( 222 + 4 ) * 55 ) - 100 / 7 * 5 - 5 * 10 =
	// input2 : 10+(3-2)*4
	//char* src = "(( 222 + 4 ) * 55 ) - 100 / 7 * 5 - 5 * 10 =";
	
	//printf("����ǥ�� ���� : %s\n", src);
	infix_to_postfix(szBuffer, postfix);
	printf("���� ǥ�� ���� : %s\n", postfix);
	printf("��� : %.15lf\n", eval(postfix));

	return 0;
}
