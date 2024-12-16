#include "Employee.h"
#include "Book.h"
#include "Map.h"
#include <iostream>

typedef unsigned int ID;
typedef Map<ID, Employee> EmployeeDatabase;
typedef Map<std::string, Book> BookLibrary;

using namespace std;

void addEmployees(EmployeeDatabase& database);
void modifyEmployees(EmployeeDatabase& database);
void addBooks(BookLibrary& library);
void modifyBooks(BookLibrary& library);

int main() {
	EmployeeDatabase employeeDatabase;
	addEmployees(employeeDatabase);

	EmployeeDatabase newEmployeeDatabase = employeeDatabase;
	newEmployeeDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43));
	modifyEmployees(newEmployeeDatabase);

	cout << "Original employee database:" << endl << employeeDatabase << endl;
	cout << "Modified employee database:" << endl << newEmployeeDatabase << endl;

	employeeDatabase = newEmployeeDatabase;

	cout << "Employee database after the assignment:" << endl << employeeDatabase << endl;

	employeeDatabase.remove(510212881);

	cout << "Employee database after removing a record:" << endl << employeeDatabase << endl;

	BookLibrary library;
	addBooks(library);

	BookLibrary newLibrary = library;
	newLibrary.add("The Catcher in the Rye", Book("J.D. Salinger", "Fiction", 214, true));
	modifyBooks(newLibrary);

	cout << "Original book library:" << endl << library << endl;
	cout << "Modified book library:" << endl << newLibrary << endl;

	library = newLibrary;

	cout << "Book library after the assignment:" << endl << library << endl;

	library.remove("1984");

	cout << "Book library after removing a record:" << endl << library << endl;

	try {
		employeeDatabase.add(761028073, Employee("Duplicate Employee", "position", 30));
	} catch (const keyAlreadyExists& e) {
		cout << e.what() << endl;
	}

	Employee* employee = employeeDatabase.find(999999999);
	if (employee == nullptr) {
		cout << "Employee not found" << endl;
	}

	Book* book = library.find("Non-existent Book");
	if (book == nullptr) {
		cout << "Book not found" << endl;
	}

	return 0;
}

void addEmployees(EmployeeDatabase& database) {
	database.add(761028073, Employee("Jan Kowalski", "salesman", 28));
	database.add(510212881, Employee("Adam Nowak", "storekeeper", 54));
	database.add(730505129, Employee("Anna Zaradna", "secretary", 32));
}

void modifyEmployees(EmployeeDatabase& database) {
	Employee* employeePtr;

	employeePtr = database.find(510212881);
	if (employeePtr != nullptr) {
		employeePtr->position = "salesman";
	}

	employeePtr = database.find(761028073);
	if (employeePtr != nullptr) {
		employeePtr->age = 29;
	}
}

void addBooks(BookLibrary& library) {
	library.add("The Great Gatsby", Book("F. Scott Fitzgerald", "Fiction", 180, true));
	library.add("1984", Book("George Orwell", "Dystopian", 328, false));
	library.add("To Kill a Mockingbird", Book("Harper Lee", "Fiction", 281, true));
}

void modifyBooks(BookLibrary& library) {
	Book* bookPtr;

	bookPtr = library.find("1984");
	if (bookPtr != nullptr) {
		bookPtr->setOnBookshelf(true);
	}

	bookPtr = library.find("The Great Gatsby");
	if (bookPtr != nullptr) {
		bookPtr->setPages(200);
	}
}
