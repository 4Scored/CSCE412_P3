#include <iostream>
#include <random>
#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"

using namespace std;

int main() {
    
    // For Random Request adding when running through cycles
    static std::random_device rd;
    static std::mt19937 rng(rd()); 
    static std::uniform_int_distribution<int> distAddReq(1, 3);  // Cycle Time

    // Get Input (# of web servers and time to run)
    int numWebServers = 0, numTotalCycles = 0;
    cout << "Number of Web Servers: ";
    cin >> numWebServers;
    cout << "Number of Cycles to run for: ";
    cin >> numTotalCycles;
    cout << endl;

    LoadBalancer loadBalancer(numWebServers);
    
    // Generating full request queue (numWebServers * 100)
    for (int req = 0; req < numWebServers * 100; req++) { 
        loadBalancer.createRequest();
    }

    // Run through cycles
    for (int cycle = 1; cycle <= numTotalCycles; cycle++) {
        cout << "Clock Cycle #" << cycle << " -- " << endl;
                
        if (distAddReq(rng) == 1) { // 33% of new request            
            loadBalancer.createRequest();
            cout << "Request added\n";
        }
        // Below Run Automatically
        loadBalancer.assignRequests();
        loadBalancer.processRequests();
        loadBalancer.scaleUp();
        loadBalancer.scaleDown();
        cout << endl;
    }
    return 0;
}