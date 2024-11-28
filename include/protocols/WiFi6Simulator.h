#ifndef WIFI6SIMULATOR_H
#define WIFI6SIMULATOR_H

#include "../../include/core/Simulator.h"

class WiFi6Simulator : public Simulator {
private:
    int subChannelWidth;  // Sub-channel width (2 MHz, 4 MHz, or 10 MHz)
    int numPacketsPerUser; // Number of packets per user (to be set in runSimulation)

public:
    WiFi6Simulator(int numUsers, int bandwidth);
    void runSimulation() ;  // Run the WiFi 6 simulation
    double calculateThroughput();   // Calculate throughput for the WiFi 6 scenario
    double calculateAverageLatency();  // Calculate the average latency for the simulation
    double calculateMaxLatency();     // Calculate the max latency for the simulation
};

#endif // WIFI6SIMULATOR_H
