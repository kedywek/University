#include "Stack.h"
#include <iostream>
#include <stdlib.h>

#define INITIAL_SIZE 16

Stack::Stack(){
	this->top = 0;
	this->data = (int*)malloc(INITIAL_SIZE * sizeof(int));
	this->size = INITIAL_SIZE;
	if (this->data == NULL)
	{
		std::cout<<"Failed to alocate memory"<<std::endl;
	}
};

Stack::~Stack(){
	this->top = 0;
	free(this->data);
};

Stack::Stack(const Stack &stack){
	this->top = stack.top;
	this->size = stack.size;
	this->data = (int*)malloc(this->size * sizeof(int));
	if (this->data == NULL)
	{
		std::cout<<"Failed to alocate memory"<<std::endl;
	}
	for (unsigned int i = 0; i < this->top; i++)
	{
		this->data[i] = stack.data[i];
	}
};

Stack& Stack::operator=(const Stack &stack){
	if(this == &stack){
		return *this;
	}
	this->top = stack.top;
	if(this->size != stack.size){
		this->size = stack.size;
		int *newData = (int*)realloc(this->data, this->size * sizeof(int));
		if (newData == NULL)
		{
			std::cout<<"Failed to alocate memory"<<std::endl;
			free(this->data);
			exit(1);
		}
		else{
			this->data = newData;
		}
	}
	for (unsigned int i = 0; i < this->top; i++){
		this->data[i] = stack.data[i];
	}
	return *this;
};

void Stack::push(int a){
	if(this->top + 1 > this->size){
		this->size *= 2;
		int *newData = (int*)realloc(this->data, size * sizeof(int));
		if (newData == NULL)
		{
			std::cout<<"Failed to alocate memory"<<std::endl;
			free(this->data);
			exit(1);
		}
		else
		{
			this->data = newData;
		}
	}
	this->data[this->top] = a;
	this->top++;
};

int Stack::pop(){
	if(this->isEmpty()){
		std::cout<<"Stack is empty"<<std::endl;
		free(this->data);
		exit(1);
	}else{
		this->top--;
		if (this->top < this->size / 2 && this->size > INITIAL_SIZE)
		{
			this->size /= 2;
			int *newData = (int*)realloc(data, size * sizeof(int));
			if (newData == NULL)
			{
				std::cout<<"Failed to alocate memory"<<std::endl;
				free(this->data);
				exit(1);
			}
			else
			{
				this->data = newData;
			}
		}
		return this->data[this->top];
	}
};

bool Stack::isEmpty(){
	if(this->top==0){
		return 1;
	}else{
		return 0;
	}
};

int Stack::checkSize(){
	return this->size;
};

int* Stack::addressOfdata(){
	return this->data;
}