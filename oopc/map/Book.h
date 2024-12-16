#pragma once
#include <string>
#include <iostream>

class Book {
public:
    Book(const std::string& author, const std::string& category, unsigned int pages, bool onBookshelf);

    std::string getAuthor() const;
    std::string getCategory() const;
    unsigned int getPages() const;
    bool isOnBookshelf() const;

    void setAuthor(const std::string& author);
    void setCategory(const std::string& category);
    void setPages(int pages);
    void setOnBookshelf(bool onBookshelf);

private:
    std::string author;
    std::string category;
    unsigned int pages;
    bool onBookshelf;
};

std::ostream& operator<<(std::ostream& os, const Book& book);
