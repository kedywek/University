#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define INITIAL_SIZE 16

typedef struct {
	unsigned int top;
	unsigned int maxLen;
	int* data;
} Stack;

void init(Stack* s);
void destroy(Stack* s);
void push(Stack* s, int element);
void* extendData(void *data, int newSize);
int pop(Stack* s);
bool isEmpty(const Stack* s);

#endif 
