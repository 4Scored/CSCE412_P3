#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
#include <string>
#include <fstream>

using namespace std;

/**
 * @file WebServer.h
 * @brief Defines the WebServer class, which simulates a server that processes web requests.
 */

 /**
 * @class WebServer
 * @brief Represents a single web server that processes one request at a time.
 * 
 * The WebServer tracks whether it's currently busy, how much time is left on its current request,
 * and logs processing events to an external file.
 */
class WebServer {            
    public:
        /**
         * @brief Unique identifier for the server.
         */
        int serverID;
        
        /**
         * @brief Remaining time to complete the currently assigned request.
         */
        int processTimeLeft;
        
        /**
         * @brief Identifier string (IP) for the current request being processed.         
         */
        string processingRequestID;
        
        /**
         * @brief Reference to the shared log file stream for recording server activity.
         */
        ofstream& lbLogger;
        
        /**
         * @brief Flag indicating if the server is available to take a new request.
         */
        bool isFree;

        /**
         * @brief Constructs a WebServer with the given ID and log file reference.
         * @param id Unique identifier for this server.
         * @param logger Reference to the log file stream for writing logs.
         */
        WebServer(const int id, ofstream& logger);

        /**
         * @brief Processes one clock cycle of the current request.
         * 
         * If the server is busy, this function decrements the remaining time.
         * If the request is completed, the server is marked as free and logged in the log file stream.
         * 
         * @return True if the server is now free after processing, false otherwise.
         */
        bool processRequest();

        /**
         * @brief Assigns a new request to this server for processing.
         * 
         * Initializes processing time, sets the processingRequestID, and marks the server as busy.
         * 
         * @param request The request to be processed by this server.
         */
        void getRequestToProcess(const Request& request);

        /**
         * @brief Checks whether the server is available to take a new request.
         * 
         * @return True if the server is free, false if it's currently processing a request.
         */
        bool checkAvailability();

};

#endif 