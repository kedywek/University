#pragma once

class Stack
{
public:
	void push(int a);
	int pop();
	bool isEmpty();
	int checkSize();
	Stack();
	~Stack();
private:
	unsigned int top, size;
	int* data;
};
 
