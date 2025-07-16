#include "WebServer.h"

WebServer::WebServer(const int id) {
    this->serverID = id; 
    this->processTime = 0;
    this->isFree = true;
}

void WebServer::getRequestToProcess(const Request& request) {
    this->processTime = request.processTime;
    this->isFree = false;
}

void WebServer::processRequest(const Request& request) {
    if (!this->isFree) { // If not free, its taken a request
        this->processTime--; // Decrement current request's process time
        if (this->processTime <= 0) {
            this->isFree = true; // Freed after process time is up
        }
    }
}

bool WebServer::checkAvailability() {
    return this->isFree;
}