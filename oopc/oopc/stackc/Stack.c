#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

void init (Stack* s){
	s->maxLen = INITIAL_SIZE;
	s->top = 0;
	s->data = malloc(INITIAL_SIZE * sizeof(int));
	if (s->data == NULL)
	{
		fprintf(stderr, "Failed to allocate memory at function extendData\n");
	}
	
}

void push(Stack* s, int element){
	if(s->top + 1 > s->maxLen){
		s->data = extendData(s->data, s->maxLen);
		s->maxLen *= 2;
	}
	s->data[s->top] = element;
	s->top++;
}

int pop(Stack* s){
	if(isEmpty(s)){
		fprintf(stderr, "Stack is empty\n");
		return -1;
	}

	s->top--;
	return s->data[s->top];
}

void* extendData(void *data, int newSize)
{
	char *newData = realloc(data, newSize*2 * sizeof(int));
    if (newData == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory at function extendData\n");
        return NULL;
    }
    else
    {
        return newData;
    }
}

void destroy(Stack* s){
	free(s->data);
}

bool isEmpty(const Stack* s){
	return s->top == 0;
}