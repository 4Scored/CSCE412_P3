#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Request.h"
#include "WebServer.h"
#include <queue>
#include <vector>
using namespace std;

/**
 * @file LoadBalancer.h
 * @brief Declares the LoadBalancer class, which manages a group of WebServers and distributes incoming requests.
 */

/**
 * @class LoadBalancer
 * @brief Simulates a load balancer that distributes requests to multiple WebServers.
 * 
 * The LoadBalancer handles request creation, request assignment, processing by servers,
 * and dynamic scaling of the number of active WebServers. It maintains a queue of requests
 * and controls the lifecycle of server operations.
 */
class LoadBalancer {  

    private:
        /**
         * @brief Initial number of WebServers requested by the user.
         */
        int numWebServers;

        /**
         * @brief Total number of requests that have been processed.
         */
        int totalProcessedRequests;

        /**
         * @brief Queue storing requests waiting to be assigned to WebServers.
         */
        queue<Request> requestQueue;
        
        /**
         * @brief List of WebServers currently active in the system.
         */
        vector<WebServer> servers;
        
        /**
         * @brief Reference to a log file stream for writing system activity.
         */
        ofstream& lbLogger;

    public:
        /**
         * @brief Constructs a LoadBalancer with a specified number of servers and a logger.
         * 
         * @param num Number of initial WebServers.
         * @param logger Reference to an output file stream for logging.
         */
        LoadBalancer(const int num, ofstream& logger);

        /**
         * @brief Creates a new request with random IP addresses and processing time.
         */
        void createRequest();
        
        /**
         * @brief Assigns pending requests in the queue to available WebServers.
         */
        void assignRequests();
        
        /**
         * @brief Processes one clock cycle for each WebServer.
         */
        void processRequests();

        /**
         * @brief Dynamically adds a WebServer if the request queue exceeds the scale-up threshold.
         */
        void scaleUp();

        /**
         * @brief Dynamically removes an idle WebServer if the request queue is small enough.
         */
        void scaleDown();

        /**
         * @brief Checks whether there are more requests in the request queue.
         * 
         * @return true if the request queue is not empty; false otherwise.
         */
        bool checkIfMoreRequests();

        /**
         * @brief Returns the total number of processed requests.
         * 
         * @return Number of completed requests.
         */
        int getTotalRequestsProcessed();

        /**
         * @brief Returns the current number of unprocessed requests in the queue.
         * 
         * @return Size of the request queue.
         */
        int getRequestQueueSize();

        /**
         * @brief Logs the final status of all WebServers and any leftover or discarded requests.
         */
        void endingServerStatuses();

};

#endif 