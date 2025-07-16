#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Request.h"
#include "WebServer.h"
#include <queue>
#include <vector>
using namespace std;

class LoadBalancer {  

    int numWebServers;
    queue<Request> requestQueue;
    vector<WebServer> servers;

    LoadBalancer(const int num);

    void createRequest();
    
    void assignRequests();
    
    void processRequest();

    void scaleUp();

    void scaleDown();

    bool checkIfMoreRequests();

};

#endif 