#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"
#include <iostream>
#include <random>
#include <fstream>

using namespace std;

/**
 * @file main.cpp
 * @brief Entry point for the Load Balancer simulation project.
 *
 * This program simulates web request handling by a configurable number of web servers
 * using a LoadBalancer class. It supports dynamic scaling, random request generation,
 * and logs activity to an output file. The simulation proceeds over a user-defined
 * number of clock cycles.
 */

 /**
 * @brief Main driver function for the load balancer simulation.
 *
 * Prompts the user for input (number of web servers and number of clock cycles),
 * initializes the load balancer with a full queue of requests, and simulates
 * each clock cycle by potentially adding new requests, assigning requests to
 * servers, processing them, and scaling the server pool. Logs are written to
 * "loadBalancerLog.txt".
 *
 * @return int Returns 0 upon successful completion; 1 if log file fails to open.
 */
int main() {
    
    // For logging purposes    
    std::ofstream lbLogger("loadBalancerLog.txt");
    if (!lbLogger.is_open()) {
        cerr << "Failed to open log file" << endl;
        return 1;
    }
    lbLogger << "----------------" << endl;

    // For Random Request adding when running through cycles
    static std::random_device rd;
    static std::mt19937 rng(rd()); 
    static std::uniform_int_distribution<int> distAddReq(1, 3); // Cycle Time
    static std::uniform_int_distribution<int> distAddRandReqs(1, 400); // Random Bursting Cycle Time

    // Get Input (# of web servers and time to run)
    int numWebServers = 0, numTotalCycles = 0;
    cout << "Number of Web Servers: ";
    cin >> numWebServers;
    lbLogger << "Number of Web Servers: " << numWebServers << endl;
    cout << "Number of Cycles to run for: ";
    cin >> numTotalCycles;    
    lbLogger << "Number of Cycles to run for: " << numTotalCycles << endl;    
    
    lbLogger << "Starting Queue Size: " << numWebServers * 100 << endl;
    lbLogger << "Task Time Range: 4 - 10 cycles" << endl;
    lbLogger << "----------------" << endl;

    LoadBalancer loadBalancer(numWebServers, lbLogger);    

    // Generating full request queue (numWebServers * 100)
    for (int req = 0; req < numWebServers * 100; req++) { 
        loadBalancer.createRequest();
    }     

    // Run through cycles
    for (int cycle = 1; cycle <= numTotalCycles; cycle++) {
        lbLogger << "Clock Cycle #" << cycle << " -- " << endl;    
        if (distAddReq(rng) == 1) { // 33% of new request every time; 1 out of (1, 2, 3)
            loadBalancer.createRequest();      
        }
        if (distAddRandReqs(rng) % 201 == 0 ) { // There's a 1/400 chance for 50 burst requests; only 201 is divisible by itself to have a remainder of 0
            for (int req = 0; req < 50; req++) {
                loadBalancer.createRequest(); 
            }
        }
        // Below Run Automatically
        loadBalancer.assignRequests();
        loadBalancer.processRequests();
        loadBalancer.scaleUp();
        loadBalancer.scaleDown();        
    }

    lbLogger << "----------------" << endl;
    lbLogger << "Simulation Complete (with " << numTotalCycles << " clock cycles executed)" << endl;  
    lbLogger << "Ending Queue Size (Remaining Requests in Queue): " << loadBalancer.getRequestQueueSize() << endl;     
    lbLogger << "Total requests successfully completed: " << loadBalancer.getTotalRequestsProcessed() << endl;
    loadBalancer.endingServerStatuses();

    return 0;
}