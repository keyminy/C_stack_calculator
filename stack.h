#pragma once
#define MAX_SIZE 100

typedef struct stack {
	int arr[MAX_SIZE];
	int top;
} stack;

void createStack(stack* p);
void push(stack* p, int elemenet);
int pop(stack* p);
int top(stack* p);
void displayStack(stack* p);
void clearStack(stack* p);