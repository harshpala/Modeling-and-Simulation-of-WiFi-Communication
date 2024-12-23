#ifndef WIFI5SIMULATOR_H
#define WIFI5SIMULATOR_H

#include "../core/Simulator.h"
#include <vector>
#include <string>
#include <sstream>

class WiFi5Simulator : public Simulator {
private:
    std::ostringstream logStream;  // Stream to store logs

    std::vector<int> packetsRemaining;   // Tracks packets remaining for each user

    double calculateThroughput(int totalPackets, double totalTime);
    double calculateAverageLatency();
    double calculateMaxLatency();

public:
    WiFi5Simulator(int numUsers, int bandwidth);
    void runSimulation(int totalPackets, int numPacketsPerUser);

};

#endif // WIFI5SIMULATOR_H
