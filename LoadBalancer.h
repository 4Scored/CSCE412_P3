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
        queue<Request> requestQueue;
        vector<WebServer> servers;

    public:
        LoadBalancer(const int num);

        Request createRequest();
        
        void assignRequests();
        
        void processRequest();

        void scaleUp();

        void scaleDown();

        bool checkIfMoreRequests();

};

#endif 