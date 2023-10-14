#ifndef BASECATALOG_HPP
#define BASECATALOG_HPP
#include <iostream>
using namespace std;
class BaseType{
    public:
		// getters for the values, parent class
        string getTitle() const{return "";}
	    string getAuthors() const{return "";}
	    string getYear()const {return "";}
	    string getTags()const{return "";}
	    string getArtists()const {return "";}
	    string getGenre()const {return "";}
	    string getDirector() const{return "";}
	    string getStarring() const{return "";}
};
#endif