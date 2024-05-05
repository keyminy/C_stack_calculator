#pragma once
#define MAX_SIZE 100

typedef struct stack {
	double arr[MAX_SIZE];
	int top;
} stack;

void createStack(stack* p);
void push(stack* p, double elemenet);
double pop(stack* p);
double top(stack* p);
void displayStack(stack* p);
void clearStack(stack* p);
int isEmpty(stack* p);