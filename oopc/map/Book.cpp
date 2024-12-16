#include "Book.h"
#include <string>

Book::Book(const std::string& author, const std::string& category, unsigned int pages, bool onBookshelf) : author(author), category(category), pages(pages), onBookshelf(onBookshelf) {}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getCategory() const {
    return category;
}

unsigned int Book::getPages() const {
    return pages;
}

bool Book::isOnBookshelf() const {
    return onBookshelf;
}

void Book::setAuthor(const std::string& author) {
    this->author = author;
}

void Book::setCategory(const std::string& category) {
    this->category = category;
}

void Book::setPages(int pages) {
    this->pages = pages;
}

void Book::setOnBookshelf(bool onBookshelf) {
    this->onBookshelf = onBookshelf;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.getAuthor() << " (" << book.getCategory() << ", " << book.getPages() << " pages, ";
    if (book.isOnBookshelf()) {
        os << "on bookshelf)";
    } else {
        os << "not on bookshelf)";
    }
    return os;
}


