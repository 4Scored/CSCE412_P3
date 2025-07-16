#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {            
    public:
        int serverID;
        int processTimeLeft;
        bool isFree;

        WebServer(const int id);

        void processRequest();

        void getRequestToProcess(const Request& request);

        bool checkAvailability();

};

#endif 