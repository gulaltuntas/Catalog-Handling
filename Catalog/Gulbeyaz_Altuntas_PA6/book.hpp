#ifndef BOOK_HPP
#define BOOK_HPP
#include "BaseCatalog.hpp"
#include <string>


class Book : public BaseType{

    private: // our private values
    string title;
    string authors;
    string year;
    string tags;

    public:
    Book(); // default constructor
    Book(string title_, string authors_, string year_, string tags_); // constructor
    ~Book(); // destructor
    // setters and getters
    void setTitle(string title_){title = title_;}
    string getTitle() const{return title;}
    void setAuthors(string authors_){authors = authors_;}
    string getAuthors() const{return authors;}
    void setYear(string year_){year = year_;}
    string getYear() const{return year;}
    void setTags(string tags_){tags = tags_;}
    string getTags() const{return tags;}
    void setInformations(string title_, string authors_, string year_, string tags_); // =operator
    friend ostream& operator <<(ostream &outputStream, const Book& other); 
 
};


Book::Book(){
    title = "";
    authors = "";
    year = "0";
    tags = "";
}
Book::~Book(){
}
Book::Book(string title_, string authors_, string year_, string tags_) {
    this->title = title_;
    this->authors = authors_;
    this->year = year_;
    this->tags = tags_;
}
void Book::setInformations(string title_, string authors_, string year_, string tags_) { // assigning the values using this
    this->title = title_;
    this->authors = authors_;
    this->year = year_;
    this->tags = tags_;
}
ostream& operator <<(ostream &outputStream, const Book& other) {
    outputStream << "\"" << other.title << "\" \"" << other.authors << "\" \"" << other.year << "\" \"" << other.tags << "\"";
    return outputStream;
}

#endif