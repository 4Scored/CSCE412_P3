#include "Request.h"

#include <string>
using std::string;

Request::Request(const string& in, const string& out, int time) {
    this->ipIN = in;
    this->ipOUT = out;
    this->processTime = time;
}