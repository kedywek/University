#pragma once

class Stack
{
public:
	void push(int a);
	int pop();
	bool isEmpty();
	int checkSize();
	int* addressOfdata();
	Stack(const Stack& stack);
	Stack& operator=(const Stack& stack);
	Stack();
	~Stack();
private:
	unsigned int top, size;
	int* data;
};
 
