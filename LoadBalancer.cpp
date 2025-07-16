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
}

Request LoadBalancer::createRequest() {
    static std::random_device rd;
    static std::mt19937 rng(rd()); 
    static std::uniform_int_distribution<int> distIP(0, 255);  // IP byte range
    static std::uniform_int_distribution<int> distCycles(4, 10);  // Cycle Time
    
    ostringstream ipIN, ipOUT; // Only write to string
    ipIN << distIP(rng) << "." << distIP(rng) << "." << distIP(rng) << "." << distIP(rng);
    ipOUT << distIP(rng) << "." << distIP(rng) << "." << distIP(rng) << "." << distIP(rng);
    // cout << ipIN.str() << " " << ipOUT.str() << " " << distCycles(rng) << endl;   
    return Request(ipIN.str(), ipOUT.str(), distCycles(rng));
}

void LoadBalancer::assignRequests() {

}

void LoadBalancer::processRequest() {

}

void LoadBalancer::scaleUp() {

}

void LoadBalancer::scaleDown() {

}

bool LoadBalancer::checkIfMoreRequests() {
    return false;
}