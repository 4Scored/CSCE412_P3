#include <iostream>

#include "Request.h"
#include "WebServer.h"
#include "LoadBalancer.h"

using namespace std;

int main() {
    
    // Get Input (# of web servers and time to run)
    int numWebServers = 0, timeToRun = 0;
    cout << "Number of Web Servers: ";
    cin >> numWebServers;
    cout << endl;
    cout << "Number of Cycles to run for: ";
    cin >> numWebServers;
    cout << endl;

    // generate full queue (numWebServers * 100)
    

}