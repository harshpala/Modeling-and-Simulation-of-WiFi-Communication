#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include "./config.h"
#include "./AccessPoint.h"

class Simulator {
protected:
    int numUsers;

    AccessPoint accessPoint;
    int bandwidth;
    std::vector<double> latencies;
    std::vector<double> timestamps;

    const double dataRate = Config::DATA_RATE_MBPS; // Mbps (256-QAM, coding rate 5/6)

public:
    Simulator(int numUsers, int bandwidth);
    
    void runSimulation(int numIterations);
    
    virtual double calculateThroughput();
    double calculateAverageLatency();
    double calculateMaxLatency();
    void saveResultsToFile(const std::string &filename, const std::string &logData);
    
    // Virtual Destructor for proper cleanup
    virtual ~Simulator() = default;
};

#endif
