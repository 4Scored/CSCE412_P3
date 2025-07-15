#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using std::string;

struct Request {        
    
    string ipIN;
    string ipOUT;
    int processTime;

    Request(const string& ipIN, const string& ipOUT, const int processTime);
};

#endif