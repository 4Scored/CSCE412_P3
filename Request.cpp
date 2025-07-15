#include "Request.h"

#include <string>
using std::string;

Request::Request(const string& ipIN, const string& ipOUT, const int processTime) {
    this->ipIN = ipIN;
    this->ipOUT = ipOUT;
    this->processTime = processTime;
}