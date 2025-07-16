#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <string>
#include <fstream>

using namespace std;

class WebServer {            
    public:
        int serverID;
        int processTimeLeft;
        string processingRequestID;
        ofstream& lbLogger;
        bool isFree;

        WebServer(const int id, ofstream& logger);

        bool processRequest();

        void getRequestToProcess(const Request& request);

        bool checkAvailability();

};

#endif 