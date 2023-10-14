#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "catalog.hpp"
#include "book.hpp"
#include "music.hpp"
#include "movie.hpp"

using namespace std;


// declearing the types of the data.txt 
const int BOOKTYPE = 1;
const int MUSICTYPE = 2;
const int MOVIETYPE = 3;

int main() {

    ifstream filename("data.txt"); // open the data
    if(!filename.is_open()){cout << "Sorry, couldn't open the files." << endl;}

    ofstream outfile; // our out.txt file
    outfile.open("out.txt");

    string line; // to get the lines
    string type; // to get the type as if its movie or book or music
    int unique_entry = 0;  

    getline(filename, type);
        if(type == "book"){  // if first line is book then sort and search for books
            outfile << "Catalog read: " << type << endl;
            CatalogMain<Book> catalog1;
            while (getline(filename, line) && !line.empty()){
                vector<string> info;  // vector called "info" to store the datas
                catalog1.readLine(info,line,BOOKTYPE, outfile); //calling readline function
                if(info.size()!= 0) { // if size is not zero that means we used an exception
                catalog1.addItem(Book(info[0],info[1],info[2],info[3])); // storing the datas into an Item in catalogMain
                unique_entry++; 
                }
            }
            outfile << unique_entry << " unique entries " << endl;
            catalog1.doCommands(outfile); // calling the do commands function inside the catalogMain to do it
        }
         else if (type == "music"){ // if first line is music then sort and search for musics
            outfile << "Catalog read: " << type << endl; // catalog reading
            CatalogMain<Music> catalog2; // created an object to use
            while (getline(filename, line) && !line.empty()){ // get line(entries) 
                vector<string> info; // string vector called "info" to store the datas
                catalog2.readLine(info,line,MUSICTYPE, outfile);
                 if(info.size()!= 0){ 
                     catalog2.addItem(Music(info[0],info[1],info[2],info[3]));
                    unique_entry++; // with every "new" and different music we ++ the entry 
                 }
            }
            outfile << unique_entry << " unique entries " << endl;
            catalog2.doCommands(outfile);
        }
        else if(type == "movie"){ // if first line is movie we perform this acts
            outfile << "Catalog read: " << type << endl; 
            CatalogMain<Movie> catalog3; // created another object
            while (getline(filename, line) && !line.empty()){ // getting the lines until it's not empty
                vector<string> info; // created a string vector to store the datas
                catalog3.readLine(info,line,MOVIETYPE, outfile); // sending the info vector, the line we are getting, movietype and out
                if(info.size()!= 0){ 
                    catalog3.addItem(Movie(info[0],info[1],info[2],info[3],info[4]));
                    unique_entry++;
                }
            }
            outfile << unique_entry << " unique entries " << endl;
            catalog3.doCommands(outfile);
        }
    return 0;
}