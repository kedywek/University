# List your *.h files (if you do not have them in your project then leave the variable "headers" empty):
headers = Map.h Employee.h Book.h

# List your *.c files:
sources = TestEmployeeAndBook.cpp Employee.cpp Book.cpp

# Specify name of your program:
executable = myprogram

$(executable): $(headers) $(sources)
	g++ -g -Wall -pedantic $(sources) -o $(executable)

.PHONY: clean
clean:
	rm $(executable)

.PHONY: check
check: $(executable)
	valgrind --leak-check=full --track-origins=yes ./$(executable)
