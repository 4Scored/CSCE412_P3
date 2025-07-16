#include "WebServer.h"

#include <chrono>

WebServer::WebServer(const int id) {
    this->serverID = id; 
    this->processTime = 0;
    this->isFree = true;
}

void WebServer::processRequest(const Request& request) {

}

void WebServer::getRequestToProcess(const Request& request) {

}

bool WebServer::checkAvailability() {
    return this->isFree;
}