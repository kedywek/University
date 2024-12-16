#include "Stack.h"
#include <iostream>
#include <stdlib.h>

void addNumbers(Stack* stack,int n);
void popNumbers(Stack* stack,int n);

int main(){
    Stack stack;
    addNumbers(&stack, 100);
    popNumbers(&stack, 100);
    addNumbers(&stack, 10);
    addNumbers(&stack, 10);
    addNumbers(&stack, 10);
    popNumbers(&stack, 10);
    popNumbers(&stack, 10);
    popNumbers(&stack, 10);
    
return 0;
}
void addNumbers(Stack* stack,int n){
    for (int i = 1; i <= n; i++)
    {
        stack->push(i);
    }
}
void popNumbers(Stack* stack,int n){
    for (int i = 1; i <= n; i++)
    {
        std::cout<<stack->pop()<<std::endl;
    }
}