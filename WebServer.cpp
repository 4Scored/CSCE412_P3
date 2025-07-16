#include <iostream>
#include "WebServer.h"

using namespace std;

WebServer::WebServer(const int id) {
    this->serverID = id;
    this->processingRequestID = "";
    this->processTimeLeft = 0;
    this->isFree = true;
}

void WebServer::processRequest() {
    if (!this->isFree) { // If not free, its taken a request
        this->processTimeLeft--; // Decrement current request's process time
        if (this->processTimeLeft <= 0) {
            this->isFree = true; // Freed after process time is up
            cout << "Server #" << this->serverID << " has processed Request from " << this->processingRequestID << endl;
        }
    }
}

void WebServer::getRequestToProcess(const Request& request) {
    this->processTimeLeft = request.processTime;
    this->processingRequestID = request.ipIN;
    this->isFree = false;
}

bool WebServer::checkAvailability() {
    return this->isFree;
}