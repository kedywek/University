all: main

main: main.c
	 gcc -fsanitize=undefined -g $^ -o $@  -lm

.c.o: 
	 gcc -fsanitize=undefined -g -Wall -pedantic -c  $<
	
main.o: main.c

clean:
	main

