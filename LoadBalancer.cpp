#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"
#include <queue>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <sstream>
using namespace std;

LoadBalancer::LoadBalancer(const int num) {
    this->numWebServers = num;
    for (int i = 0; i < num; i++) {
        this->servers.push_back(WebServer(i)); // Add WebServer Instanes according to user input
        cout << "WebServer #" << i << " has been created." << endl;
    }    
}

Request LoadBalancer::createRequest() {
    static std::random_device rd;
    static std::mt19937 rng(rd()); 
    static std::uniform_int_distribution<int> distIP(0, 255);  // IP byte range
    static std::uniform_int_distribution<int> distCycles(4, 10);  // Cycle Time

    ostringstream ipIN, ipOUT; // Only need to write to stringstreams
    ipIN << distIP(rng) << "." << distIP(rng) << "." << distIP(rng) << "." << distIP(rng);
    ipOUT << distIP(rng) << "." << distIP(rng) << "." << distIP(rng) << "." << distIP(rng);
    // cout << ipIN.str() << " " << ipOUT.str() << " " << distCycles(rng) << endl;   
    return Request(ipIN.str(), ipOUT.str(), distCycles(rng));
}

void LoadBalancer::assignRequests() {
    for (auto& server : this->servers) {    
        if (server.checkAvailability() && this->checkIfMoreRequests()) { // Check if there's an available server and more requests exist
            Request req = this->requestQueue.front(); // Take a request from the request queue
            this->requestQueue.pop(); // Pop it from the request queue
            server.getRequestToProcess(req); // Assign the Request to the Server
        }
    }
}

void LoadBalancer::processRequest() {

}

void LoadBalancer::scaleUp() {

}

void LoadBalancer::scaleDown() {

}

bool LoadBalancer::checkIfMoreRequests() {
    return !this->requestQueue.empty();
}