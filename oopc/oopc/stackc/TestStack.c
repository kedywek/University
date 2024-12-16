#include "Stack.c"

int main(){
	Stack s;
	init(&s);
	for (int i = 0; i < 100; i++){
		push(&s, i);
	}
	while(!isEmpty(&s)){
		printf("%d\n", pop(&s));
	}
	pop(&s);
	destroy(&s);
}