#include "catalog.hpp"
#include "BaseCatalog.hpp"
#include "movie.hpp"
#include "book.hpp"
#include "music.hpp"
#include <iostream>
using namespace std;


    class Exception{ // exception classes
	public:
	    string what() const {return "base exception";}
    };

    // missing field exception
    class MissingField : public Exception{
	public:
	    string what() const {return "missing field";}
    };

    // duplicate entry exception
    class DuplicateEntry : public Exception{
	public:
	    string what() const {return "duplicate entry";}
    };

    // wrong command exception
    class WrongCommand : public Exception{
	public:
	    string what() const {return "command is wrong";}
    };
    
