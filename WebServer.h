#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {            

    int serverID;
    int processTimeLeft;
    bool isFree;

    WebServer(const int serverID);

    void processRequest(const Request& request);

    void getRequestToProcess(const Request& request);

    bool checkAvailability();

};

#endif 