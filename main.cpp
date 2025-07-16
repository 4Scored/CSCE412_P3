#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"
#include <iostream>
#include <random>
#include <fstream>

using namespace std;

int main() {
    
    // For logging purposes    
    std::ofstream lbLogger("loadBalancerLog.txt");
    if (!lbLogger.is_open()) {
        std::cerr << "Failed to open log file" << endl;
        return 1;
    }

    // For Random Request adding when running through cycles
    static std::random_device rd;
    static std::mt19937 rng(rd()); 
    static std::uniform_int_distribution<int> distAddReq(1, 3); // Cycle Time
    static std::uniform_int_distribution<int> distAddRanReqs(200, 300); // Random Bursting Cycle Time

    // Get Input (# of web servers and time to run)
    int numWebServers = 0, numTotalCycles = 0;
    cout << "Number of Web Servers: ";
    cin >> numWebServers;
    lbLogger << "Number of Web Servers: " << numWebServers << endl;
    cout << "Number of Cycles to run for: ";
    cin >> numTotalCycles;
    cout << endl;
    lbLogger << "Number of Cycles to run for: " << numTotalCycles << endl;    

    LoadBalancer loadBalancer(numWebServers, lbLogger);
    
    // Generating full request queue (numWebServers * 100)
    for (int req = 0; req < numWebServers * 100; req++) { 
        loadBalancer.createRequest();
    }

    // Run through cycles
    for (int cycle = 1; cycle <= numTotalCycles; cycle++) {
        lbLogger << "Clock Cycle #" << cycle << " -- " << endl;    
        if (distAddReq(rng) == 1) { // 33% of new request every time
            loadBalancer.createRequest();      
        }
        if (cycle % 300 == 0 ) { // For every 300 cycles, there is a burst of 50 requests
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
    lbLogger << "Total requests successfully completed: " << loadBalancer.getTotalRequestsProcessed();

    return 0;
}