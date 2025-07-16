#include "WebServer.h"
#include <iostream>
#include <fstream>

using namespace std;

WebServer::WebServer(const int id, ofstream& logger) : 
    serverID(id), processTimeLeft(0), processingRequestID(""), lbLogger(logger), isFree(true) {} 

bool WebServer::processRequest() {
    if (!this->isFree) { // If not free, its taken a request
        this->processTimeLeft--; // Decrement current request's process time
        if (this->processTimeLeft <= 0) {
            this->isFree = true; // Freed after process time is up
            this->lbLogger << "Server #" << this->serverID << " has finished processing Request from " << this->processingRequestID << endl;
            return true;
        }
    }
    return false;
}

void WebServer::getRequestToProcess(const Request& request) {
    this->processTimeLeft = request.processTime;
    this->processingRequestID = request.ipIN;
    this->isFree = false;
}

bool WebServer::checkAvailability() {
    return this->isFree;
}