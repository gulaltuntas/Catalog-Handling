#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "BaseCatalog.hpp"


class Music : public BaseType{
    
    private: // our private values
    string title;
    string artists;
    string year;
    string genre;

    public:

    Music(); // default constructor
    Music(string title_, string artists_, string year_, string genre_); // constructor
    //setters and getters to take the values
    void setTitle(string title_){title = title_;}
    string getTitle() const{return title;}
    void setArtists(string artists_){artists = artists_;}
    string getArtists() const{return artists;}
    void setYear(string year_){year = year_;}
    string getYear() const{return year;}
    void setGenre(string genre_){genre = genre_;}
    string getGenre() const{return genre;}
    void setInformations(string title_, string artists_, string year_, string genre_); // settting the given values 
    friend ostream& operator <<(ostream &outputStream, const Music& other); 
    ~Music();
};

Music::Music(){
    title = "";
    artists = "";
    year = "0";
    genre = "";
}
Music::Music(string title_, string artists_, string year_, string genre_) {
    this->title = title_;
    this->artists = artists_;
    this->year = year_;
    this->genre = genre_;
}
void Music::setInformations(string title_, string artists_, string year_, string genre_) {
    this->title = title_;
    this->artists = artists_;
    this->year = year_;
    this->genre = genre_;
}

Music::~Music(){
}
ostream& operator <<(ostream &outputStream, const Music& other) {
    outputStream << "\"" << other.title << "\" \"" << other.artists << "\" \"" << other.year << "\" \"" << other.genre << "\"";
    return outputStream;
}
#endif