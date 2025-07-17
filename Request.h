#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using std::string;

/**
 * @file Request.h
 * @brief Defines the Request struct used to simulate web requests in the load balancer system.
 */

/**
 * @struct Request
 * @brief Represents a single web request to be handled by a web server.
 * 
 * Each Request contains:
 * - An input IP address (ipIN) representing the source of the request.
 * - An output IP address (ipOUT) representing the destination for the response.
 * - A process time indicating how many clock cycles the request needs to complete.
 */
struct Request {        
    
    /**
     * @brief The incoming IP address of the request origin.
     */
    string ipIN;
    
    /**
     * @brief The outgoing IP address where the result is sent.
     */
    string ipOUT;
    
    /**
     * @brief The number of clock cycles needed to process this request.
     */
    int processTime;

    /**
     * @brief Constructs a new Request.
     * 
     * @param in The incoming IP address (source).
     * @param out The outgoing IP address (destination).
     * @param time The number of clock cycles required to process the request.
     */
    Request(const string in, const string out, const int time);
};

#endif