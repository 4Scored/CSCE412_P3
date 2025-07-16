#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Request.h"
#include "WebServer.h"
#include <queue>
#include <vector>
using namespace std;

class LoadBalancer {  

    private:
        int numWebServers;
        int totalProcessedRequests;
        queue<Request> requestQueue;
        vector<WebServer> servers;
        ofstream& lbLogger;

    public:
        LoadBalancer(const int num, ofstream& logger);

        void createRequest();
        
        void assignRequests();
        
        void processRequests();

        void scaleUp();

        void scaleDown();

        bool checkIfMoreRequests();

        int getTotalRequestsProcessed();

};

#endif 