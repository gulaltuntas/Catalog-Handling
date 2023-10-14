#ifndef MOVIE_HPP
#define MOVIE_HPP
#include "BaseCatalog.hpp"


class Movie : public BaseType{

    private: // our private values + starring which is only for movie
    string title;
    string director;
    string year;
    string genre;
    string starring;

    public:
    Movie(); // default constructor
    Movie(string title_, string director_, string year_, string genre_, string starring_); // constructor 
    // setters and getters
    void setTitle(string title_){title = title_;} 
    string getTitle() const{return title;}
    void setDirector(string director_){director = director_;}
    string getDirector() const{return director;}
    void setYear(string year_){year = year_;}
    string getYear() const{return year;}
    void setGenre(string genre_){genre = genre_;}
    string getGenre() const{return genre;}
    void setStarring(string starring_){starring = starring_;}
    string getStarring() const{return starring;}
    void setInformations(string title_, string director_, string year_, string genre_, string starring_); // setting the informations
    friend ostream& operator <<(ostream &outputStream, const Movie& other);
    ~Movie(); // destructor
};



Movie::Movie(){

    title = "";
    director = "";
    year = "0";
    genre = "";
    starring = "";

}
Movie::Movie(string title_, string director_, string year_, string genre_, string starring_) {
    this->title = title_;
    this->director = director_;
    this->year = year_;
    this->genre = genre_;
    this->starring = starring_;
}

void Movie::setInformations(string title_, string director_, string year_, string genre_, string starring_) { // assigning the values using this
    this->title = title_;
    this->director = director_;
    this->year = year_;
    this->genre = genre_;
    this->starring = starring_;
}

Movie::~Movie(){   
}
ostream& operator <<(ostream &outputStream, const Movie& other) {
    outputStream << "\"" << other.title << "\" \"" << other.director << "\" \"" << other.year << "\" \"" << other.genre << "\" \"" << other.starring << "\"";
    return outputStream;
}
#endif