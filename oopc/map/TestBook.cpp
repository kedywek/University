#include "Map.h"
#include "Book.h"
#include <iostream>

int main() {
    Map<std::string, Book> library;

    // Adding books to the library
    library.add("The Great Gatsby", Book("F. Scott Fitzgerald", "Fiction", 180, true));
    library.add("1984", Book("George Orwell", "Dystopian", 328, false));
    library.add("To Kill a Mockingbird", Book("Harper Lee", "Fiction", 281, true));

    // Finding a book
    Book* book = library.find("1984");
    if (book != nullptr) {
        std::cout << "Found book: " << book->getAuthor() << ", " << book->getCategory() << ", " << book->getPages() << " pages, " << (book->isOnBookshelf() ? "On Bookshelf" : "Borrowed") << std::endl;
    } else {
        std::cout << "Book not found" << std::endl;
    }

    // Printing all books in the library
    std::cout << "Library contents:" << std::endl;
    std::cout << library;

    // Removing a book
    library.remove("The Great Gatsby");

    // Printing all books in the library after removal
    std::cout << "Library contents after removal:" << std::endl;
    std::cout << library;

    return 0;
}