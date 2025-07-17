#include "Request.h"

#include <string>
using std::string;

/**
 * @file Request.cpp
 * @brief Implements the constructor for the Request struct, which represents a simulated web request.
 */

/**
 * @brief Constructs a new Request object.
 * 
 * Initializes a Request with an input IP, output IP, and a required processing time.
 * 
 * @param in The incoming IP address (request origin).
 * @param out The outgoing IP address (response destination).
 * @param time The number of clock cycles required to process the request.
 */
Request::Request(const string in, const string out, int time) {
    this->ipIN = in;
    this->ipOUT = out;
    this->processTime = time;
}