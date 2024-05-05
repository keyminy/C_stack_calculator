#include "stack.h"

void createStack(stack* p) {
	p->top = -1;
}

void push(stack* p, double elemenet) {
	if (p->top == MAX_SIZE - 1) {
		printf("stack overflow!!\n");
		return;
	}
	p->arr[++(p->top)] = elemenet;
}

double  pop(stack* p) {
	if (p->top == -1) {
		return -1; // sack is empty
	}
	return p->arr[(p->top)--];
}
double  top(stack* p) {
	if (p->top == -1) {
		return -1; // sack is empty
	}
	return p->arr[p->top];
}

void displayStack(stack* p) {
	printf("stack display\n");
	for (int i = p->top; i >= 0; i--) {
		printf("%d ", p->arr[i]);
	}
	puts("");
}
void clearStack(stack* p)
{
	p->top = -1;
}
int isEmpty(stack* s) {
	return s->top == -1;
}