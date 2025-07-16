#include "WebServer.h"

WebServer::WebServer(const int id) {
    this->serverID = id; 
    this->processTimeLeft = 0;
    this->isFree = true;
}

void WebServer::getRequestToProcess(const Request& request) {
    this->processTimeLeft = request.processTime;
    this->isFree = false;
}

void WebServer::processRequest(const Request& request) {
    if (!this->isFree) { // If not free, its taken a request
        this->processTimeLeft--; // Decrement current request's process time
        if (this->processTimeLeft <= 0) {
            this->isFree = true; // Freed after process time is up
        }
    }
}

bool WebServer::checkAvailability() {
    return this->isFree;
}