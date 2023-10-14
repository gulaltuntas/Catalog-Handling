#ifndef CATALOG_HPP
#define CATALOG_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "book.hpp"
#include "movie.hpp"
#include "music.hpp"
#include <stdexcept>
#include "BaseCatalog.hpp"
#include "exceptions.hpp"
using namespace std;



template<class T>
class CatalogMain{
    private:
        vector<T> name;  // our template vector to hold the values in it (music vector, movie vector, book vector)
    public:
    
        CatalogMain(){} // default 
        ~CatalogMain(){} // destructor
        void addItem(T item);  // to store the values into the item
        void readLine(vector<string>& info,string line,int type, ofstream &outfile); // function to read and parse the lines
        void doCommands(ofstream &outfile); // command file
        void doSearch(string& searchString, string& field, ofstream &outfile); // command file divides into two as do sort and do searcj
        void doSort(string& searchString, ofstream &outfile);

        // all the search functions that gets the different values
        void searchTitle( string& searchString, ofstream &outfile);
        void searchAuthor( string& searchString, ofstream &outfile);
        void searchYear( string& searchString, ofstream &outfile);
        void searchTags( string& searchString, ofstream &outfile);
        void searchDirector( string& searchString, ofstream &outfile);
        void searchArtists(string& searchString, ofstream &outfile);
        void searchGenre(string& searchString, ofstream &outfile);
        void searchStarring( string& searchString, ofstream &outfile);

        // sorting functions to return the smaller one 
        void sortTitle(string& searchString);
        void sortAuthor(string& searchString);
        void sortYear(string& searchString);
        void sortTags(string& searchString);
        void sortActors(string& searchString);
        void sortArtists(string& searchStringe);
        void sortDirector(string& searchString);
};

template <class T>
void CatalogMain<T>::addItem(T item){
    name.push_back(item);   // using push back we add the item to the our name object 
}

template <class T>
void CatalogMain<T>::readLine(vector<string>& info,string itemLine,int type, ofstream &outfile) {
    
    string title,field2,year,field4,actors; // five string values for the 5 inputs
            size_t pos1, pos2;
            pos1 = itemLine.find('"'); // finding the two " " so it can store the data between them
            pos2 = itemLine.find('"', pos1 + 1);
            title = itemLine.substr(pos1 + 1, pos2 - pos1 - 1); // title, common for all
            info.push_back(title); // adding title to the vector

            pos1 = itemLine.find('"', pos2 + 1); // finding the " " and getting the value what's between them
            pos2 = itemLine.find('"', pos1 + 1);
            field2 = itemLine.substr(pos1 + 1, pos2 - pos1 - 1); // it can be author, singer, or director
            info.push_back(field2); 

            pos1 = itemLine.find('"', pos2 + 1);
            pos2 = itemLine.find('"', pos1 + 1);
            year = itemLine.substr(pos1 + 1, pos2 - pos1 - 1); // year of the product
            info.push_back(year);

            pos1 = itemLine.find('"', pos2 + 1);
            pos2 = itemLine.find('"', pos1 + 1);
            field4 = itemLine.substr(pos1 + 1, pos2 - pos1 - 1); // it can be tags or genre 
            info.push_back(field4);

            pos1 = itemLine.find('"', pos2 + 1);
            pos2 = itemLine.find('"', pos1 + 1);
            actors = itemLine.substr(pos1 + 1, pos2 - pos1 - 1); // this is only for the movie since it also has starrings
            info.push_back(actors);

           try {
                if (type == 1 || type == 2) { // since music and book only has 4 entries we seperated them as 1, 2, 3
                    if (title.empty() || field2.empty() || year.empty() || field4.empty()) {
                    throw MissingField(); // if there is any empy tag it throws a missing field error
                    }
                }
                else if (type == 3) {
                    if (title.empty() || field2.empty() || year.empty() || field4.empty() || actors.empty()) { // same for the movie
                    throw MissingField();
                    }
                }
            }
            catch (const MissingField &e) { // catching the missing field
            outfile << "Exception: " << e.what() << endl; 
            outfile << title << " " << field2 << " " << year << " " << field4;
                if (type == 3) { outfile << " " << actors << endl;}
                else { outfile << endl;}
                info.clear(); // clearing the vector from the exception
            }

         try {
            for(auto i = name.begin();i != name.end();++i) { 
                    if(title == i->getTitle()) {
                    throw DuplicateEntry(); // if any title matches with the previous one, i counted as the same so i throw an error
                    }
                }
            }
            catch (const DuplicateEntry &e) {
            outfile << "Exception: " << e.what() << endl; // printing the error to the file
            outfile << title << " " << field2 << " " << year << " " << field4; // coutting the values 
                if (type == 3) {outfile << " " << actors << endl;} // if it's movie then we add actors too
                else {outfile << endl;}
                info.clear();
            }

}


template <class T>
void CatalogMain<T>::doCommands(ofstream &outfile){

    ifstream filename("commands.txt"); // opening the command txt
    if (!filename.is_open()){cout << "There is not a command file like that." << endl;}
    string command;
    while (getline(filename, command)) { // getting the lines from the file
        istringstream iss(command);
        string action, searchString, field, in; // assign them to strings
        iss >> action; // sorting or searching
        getline(iss,searchString,'"'); // getting what's between " "
        getline(iss,searchString,'"');
        iss >> in; 
        getline(iss,field,'"');
        getline(iss,field,'"');
       try {
            if (action == "search") {
                outfile << command << endl; // printing the command into the output file
                doSearch(searchString, field, outfile); // calling the search function
            }
            else if (action == "sort") {
                outfile << command << endl; // printing the command into output file 
                doSort(searchString, outfile);
                 for (const T& item : name) { // this is for printing the sorted item into output file 
                        outfile << item << endl;
                }
            }
            else {
                throw WrongCommand(); // if error, throw
            }
        }
        catch (const WrongCommand& e) {
        outfile << e.what() << endl; // catch the error and print it to output file
        }
    }

}



template <class T>
void CatalogMain<T>::doSearch(string& searchString, string& field, ofstream &outfile){ 
    try{  // our field means what we are getting into so we are using try - catch for errors
         if (field == "title") {
            searchTitle(searchString, outfile); // sending the searchstring which the word we want to look for into the function along with outfile 
        }
        else if (field == "authors") {
            searchAuthor(searchString, outfile);
        }
        else if (field == "year") {
            searchYear(searchString, outfile);
        }
        else if (field == "tags") {
            searchTags(searchString, outfile);
        }
        else if (field == "director") {
            searchDirector(searchString, outfile);
        }
        else if (field == "artists") {
            searchArtists(searchString, outfile);
        }
        else if (field == "genre") {
            searchGenre(searchString, outfile);
        }
        else if (field == "starring") {
            searchStarring(searchString, outfile);
        }
        else{ // if the command we get is not any of these fields we are going to throw an error
            throw WrongCommand();
        }
    }catch(const WrongCommand &e){
        outfile << "Exception: " ; // throwing exception
        outfile << e.what() << endl;
    }
       
}



template <class T>
void CatalogMain<T>::doSort(string& searchString, ofstream &outfile){
    // calling the functions according to the what we want to sort
    try{
        if (searchString == "title") { 
            sortTitle(searchString); // sending the thing we want to sort into the function 
        }
        else if (searchString == "authors") {
            sortAuthor(searchString);
        }  
        else if (searchString == "year") {
            sortYear(searchString);
        }
        else if (searchString == "tags") {
            sortTags(searchString);
        }
        else if (searchString == "actors") {
            sortActors(searchString);
        }  
        else if (searchString == "artists") {
            sortArtists(searchString);
        }  
        else if (searchString == "director") {
            sortDirector(searchString);
        }  
        else{
            throw WrongCommand(); // if there is something wrong it throws an exception
        }
    }
    catch(const WrongCommand &e){
        outfile << "Exception: ";
        outfile << e.what() << endl;
    }

 
} 

template <class T>
void CatalogMain<T>::searchTitle(string& searchString, ofstream &outfile) { 
    for(auto i = name.begin();i != name.end() ;i++) { //iterating through the "name" container 
        if(i->getTitle().find(searchString) != string::npos) { // and if we find the title in the current string
            outfile << *i << endl; // cout to the file the whole string
        }
    }
}

template <class T>
void CatalogMain<T>::searchAuthor(string& searchString, ofstream &outfile){
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getAuthors().find(searchString) != string::npos) {
            outfile << *i << endl;
        }
    }
}

template <class T>
void CatalogMain<T>::searchYear(string& searchString, ofstream &outfile) {
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getYear().find(searchString) != string::npos) {
            outfile << *i << endl;
        }
    }
}

template <class T>
void CatalogMain<T>::searchTags(string& searchString, ofstream &outfile) {
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getTags().find(searchString) != string::npos) {
            outfile << *i << endl;
        }
    }
}

template <class T>
void CatalogMain<T>::searchDirector( string& searchString, ofstream &outfile) {
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getDirector().find(searchString) != string::npos) {
           outfile << *i << endl;
        }
    }
}

template <class T>
void CatalogMain<T>::searchArtists( string& searchString, ofstream &outfile) {
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getArtists().find(searchString) != string::npos) {
            outfile << *i << endl;
        }
    }
}

template <class T>
void CatalogMain<T>::searchGenre( string& searchString, ofstream &outfile) {
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getGenre().find(searchString) != string::npos) {
            outfile << *i << endl;
        }
    }
}

template <class T>
void CatalogMain<T>::searchStarring( string& searchString, ofstream &outfile) {
    for(auto i = name.begin();i != name.end() ;i++) {
        if(i->getStarring().find(searchString) != string::npos) {
            outfile << *i << endl;
        }
    }
}


template <class T>
void CatalogMain<T>::sortTitle(string& searchString){ // function to sort the titles of the strings
    sort(name.begin(), name.end(), [](const T& item1, const T& item2) { // using stl we sort the arrays 
                return item1.getTitle() < item2.getTitle(); // return the smaller one 
        });
}
    
template <class T>
void CatalogMain<T>::sortAuthor(string& searchString){    
        sort(name.begin(), name.end(), [](const T& item1, const T& item2) {
                return item1.getAuthors() < item2.getAuthors();
        });    
}

template <class T>
void CatalogMain<T>::sortYear(string& searchString){
      sort(name.begin(), name.end(), [](const T& item1, const T& item2) {
                return item1.getYear() < item2.getYear();
        });
}

template <class T>
void CatalogMain<T>::sortTags(string& searchString){
        sort(name.begin(), name.end(), [](const T& item1, const T& item2) {
                return item1.getTags() < item2.getTags();
        });
}

template <class T>
void CatalogMain<T>::sortActors(string& searchString){
        sort(name.begin(), name.end(), [](const T& item1, const T& item2) {
                return item1.getStarring() < item2.getStarring();
        });
}

template <class T>
void CatalogMain<T>::sortArtists(string& searchString){
        sort(name.begin(), name.end(), [](const T& item1, const T& item2) {
                return item1.getArtists() < item2.getArtists();
        });
}


template <class T>
void CatalogMain<T>::sortDirector(string& searchString){
       sort(name.begin(), name.end(), [](const T& item1, const T& item2) {
                return item1.getDirector() < item2.getDirector();
        });
}


#endif