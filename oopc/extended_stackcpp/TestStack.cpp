#include "Stack.h"
#include <iostream>
#include <stdlib.h>

void addNumbers(Stack* stack,int n);
void popNumbers(Stack* stack,int n);

int main(){
    Stack stack, stack3;
    addNumbers(&stack, 100);
    Stack stack2(stack);
    stack3 = stack;
    popNumbers(&stack, 100);
    popNumbers(&stack2, 100);
    popNumbers(&stack3, 100);
    return 0;
}
void addNumbers(Stack* stack, int n){
    for (int i = 1; i <= n; i++)
    {
        stack->push(i);
    }
}
void popNumbers(Stack* stack, int n){
    for (int i = 1; i <= n; i++)
    {
        std::cout<<stack->pop()<<std::endl;
    }
}