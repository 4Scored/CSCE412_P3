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

/**
 * @file LoadBalancer.cpp
 * @brief Implements the LoadBalancer class, responsible for distributing and managing web requests across web servers.
 */

// For Dynamic Server Allocation
/// Threshold for when Request Queue exceeds 40
const int scaleUpThreshold = 40;
/// Threshold for when Request Queue is less than 10
const int scaleDownThreshold = 10;
/// Minimum number of web servers to be maintained; Assuming numWebServers is 10 (as from the Instructions)
const int minServersSize = 10;
/// Maximum number of web servers allowed to prevent resource overuse; to not exceed 20 webservers
const int maxServersSize = 20; 

/**
 * @brief Constructs a LoadBalancer with a given number of initial web servers and a log file.
 * 
 * @param num Number of initial web servers.
 * @param logger Reference to the output log file stream.
 */
LoadBalancer::LoadBalancer(const int num, ofstream& logger) : numWebServers(num), lbLogger(logger) {    
    for (int i = 1; i <= this->numWebServers; i++) {
        this->servers.push_back(WebServer(i, lbLogger)); // Add WebServer Instanes according to user input
        this->lbLogger << "WebServer " << i << " has been created" << endl;
    }    
}

/**
 * @brief Creates a new web request with randomly generated IP addresses and processing time.
 * 
 * The request is added to the internal queue and logged.
 */
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

/**
 * @brief Assigns requests to available web servers from the request queue.
 */
void LoadBalancer::assignRequests() {
    for (auto& server : this->servers) {    
        if (server.checkAvailability() && this->checkIfMoreRequests()) { // Check if there's an available server and more requests exist
            Request req = this->requestQueue.front(); // Take a request from the request queue            
            this->requestQueue.pop(); // Pop it from the request queue
            server.getRequestToProcess(req); // Assign the Request to the Server
            this->lbLogger << "WebServer " << server.serverID << " assigned Request from " << req.ipIN << " to " << req.ipOUT << endl;
        }
    }
}

/**
 * @brief Processes one clock cycle for each web server.
 * 
 * If a server completes a request, the processed request counter is incremented.
 */
void LoadBalancer::processRequests() {
    for (auto& server : this->servers) {    
        if (server.processRequest()) {
            this->totalProcessedRequests++;
        }
    }
}

/**
 * @brief Dynamically adds a new server if the request queue exceeds the scale-up threshold.
 */
void LoadBalancer::scaleUp() {
    if (this->requestQueue.size() > scaleUpThreshold && this->servers.size() < maxServersSize) {
        int newID = this->servers.size() + 1; // Assign newID
        this->servers.push_back(WebServer(newID, lbLogger)); // and add it to the WebServer vector
        this->lbLogger << "Scaling up: Added WebServer " << newID << endl; 
    }
}

/**
 * @brief Dynamically removes an idle server if the request queue drops below the scale-down threshold.
 */
void LoadBalancer::scaleDown() {
    if (this->requestQueue.size() < scaleDownThreshold && this->servers.size() > minServersSize) {
        WebServer& lastServer = this->servers.back();
        if (lastServer.checkAvailability()) {
            this->lbLogger << "Scaling down: Removed WebServer " << lastServer.serverID << "\n";
            this->servers.pop_back();
        }
    }
}

/**
 * @brief Checks if the request queue contains more requests to be assigned.
 * 
 * @return true if the queue is not empty; false otherwise.
 */
bool LoadBalancer::checkIfMoreRequests() {
    return !this->requestQueue.empty();
}

/**
 * @brief Returns the total number of requests processed by all servers.
 * 
 * @return Number of processed requests.
 */
int LoadBalancer::getTotalRequestsProcessed() {
    return this->totalProcessedRequests;
}

/**
 * @brief Returns the current size of the request queue.
 * 
 * @return Number of unprocessed requests in the queue.
 */
int LoadBalancer::getRequestQueueSize() {
    return this->requestQueue.size();
}

/**
 * @brief Logs the final state of each server and the number of rejected/discarded requests.
 * 
 * Summarizes how many servers were active/inactive and how many requests were left in the queue.
 */
void LoadBalancer::endingServerStatuses() {
    int active = 0, inactive = 0, discarded = this->getRequestQueueSize();
    for (auto& server : this->servers) {    
        if (server.checkAvailability()) { // If free, it's not processing any requests, thus inactive
            inactive++;            
        } else { // else, its active
            active++;
            discarded++;
        }
    }
    this->lbLogger << "Active WebServers: " << active << endl; 
    this->lbLogger << "Inactive WebServers: " << inactive << endl; 
    this->lbLogger << "Discarded/Rejected Requests: " << discarded << endl; 
}