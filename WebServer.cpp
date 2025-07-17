#include "WebServer.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @file WebServer.cpp
 * @brief Implements the WebServer class methods, used to simulate processing web requests.
 */

/**
 * @brief Constructs a WebServer with a unique ID and a shared log stream.
 * 
 * Initializes all server state, including availability and internal timers.
 * 
 * @param id The unique identifier for this WebServer.
 * @param logger Reference to an output file stream for logging server events.
 */
WebServer::WebServer(const int id, ofstream& logger) : 
    serverID(id), processTimeLeft(0), processingRequestID(""), lbLogger(logger), isFree(true) {} 

/**
 * @brief Processes one clock cycle of the current request.
 * 
 * If the server is processing a request, this function decrements the remaining time.
 * When the request completes, the server becomes available again and logs the completion event.
 * 
 * @return true if the server has completed a request and is now free, false otherwise.
 */
bool WebServer::processRequest() {
    if (!this->isFree) { // If not free, its taken a request
        this->processTimeLeft--; // Decrement current request's process time
        if (this->processTimeLeft <= 0) {
            this->isFree = true; // Freed after process time is up
            this->lbLogger << "WebServer " << this->serverID << " has finished processing Request from " << this->processingRequestID << endl;
            return true;
        }
    }
    return false;
}

/**
 * @brief Assigns a new request to this server for processing.
 * 
 * Updates internal state with the request's processing time, processingRequestID identifier, and marks the server as busy.
 * 
 * @param request The Request object to be processed.
 */
void WebServer::getRequestToProcess(const Request& request) {
    this->processTimeLeft = request.processTime;
    this->processingRequestID = request.ipIN;
    this->isFree = false;
}

/**
 * @brief Checks if the server is currently free to handle a new request.
 * 
 * @return true if the server is not processing a request, false otherwise.
 */
bool WebServer::checkAvailability() {
    return this->isFree;
}