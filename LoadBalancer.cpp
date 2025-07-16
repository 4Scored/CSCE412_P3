#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"
#include <queue>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// For Dynamic Server Allocation
const int scaleUpThreshold = 40; // When Request Queue exceeds 40
const int scaleDownThreshold = 10; // When Request Queue is less than 10
const int minServersSize = 10; // Assuming numWebServers is 10 (as from the Instructions); can be changed
const int maxServersSize = 20; // To not exceed 20 webservers

LoadBalancer::LoadBalancer(const int num, ofstream& logger) : numWebServers(num), lbLogger(logger) {    
    for (int i = 1; i <= this->numWebServers; i++) {
        this->servers.push_back(WebServer(i, lbLogger)); // Add WebServer Instanes according to user input
        this->lbLogger << "WebServer #" << i << " has been created" << endl;
    }    
}

void LoadBalancer::createRequest() {
    static std::random_device rd;
    static std::mt19937 rng(rd()); 
    static std::uniform_int_distribution<int> distIP(0, 255);  // IP byte range
    static std::uniform_int_distribution<int> distCycles(4, 10);  // Cycle Time

    ostringstream ipIN, ipOUT; // Only need to write to stringstreams
    ipIN << distIP(rng) << "." << distIP(rng) << "." << distIP(rng) << "." << distIP(rng);
    ipOUT << distIP(rng) << "." << distIP(rng) << "." << distIP(rng) << "." << distIP(rng);
    // cout << ipIN.str() << " " << ipOUT.str() << " " << distCycles(rng) << endl;   
    Request newReq(ipIN.str(), ipOUT.str(), distCycles(rng));
    this->requestQueue.push(newReq);
    this->lbLogger << "New Request created from " << newReq.ipIN << " to " << newReq.ipOUT << endl;
}

void LoadBalancer::assignRequests() {
    for (auto& server : this->servers) {    
        if (server.checkAvailability() && this->checkIfMoreRequests()) { // Check if there's an available server and more requests exist
            Request req = this->requestQueue.front(); // Take a request from the request queue            
            this->requestQueue.pop(); // Pop it from the request queue
            server.getRequestToProcess(req); // Assign the Request to the Server
            this->lbLogger << "Server #" << server.serverID << " assigned Request from " << req.ipIN << " to " << req.ipOUT << endl;
        }
    }
}

void LoadBalancer::processRequests() {
    for (auto& server : this->servers) {    
        if (server.processRequest()) {
            this->totalProcessedRequests++;
        }
    }
}

void LoadBalancer::scaleUp() {
    if (this->requestQueue.size() > scaleUpThreshold && this->servers.size() < maxServersSize) {
        int newID = this->servers.size(); // Assign newID
        this->servers.push_back(WebServer(newID, lbLogger)); // and add it to the WebServer vector
        this->lbLogger << "Scaling up: Added server #" << newID << endl; 
    }
}

void LoadBalancer::scaleDown() {
    if (this->requestQueue.size() < scaleDownThreshold && this->servers.size() > minServersSize) {
        WebServer& lastServer = this->servers.back();
        if (lastServer.checkAvailability()) {
            this->lbLogger << "Scaling down: Removing server #" << lastServer.serverID << "\n";
            this->servers.pop_back();
        }
    }
}

bool LoadBalancer::checkIfMoreRequests() {
    return !this->requestQueue.empty();
}

int LoadBalancer::getTotalRequestsProcessed() {
    return this->totalProcessedRequests;
}