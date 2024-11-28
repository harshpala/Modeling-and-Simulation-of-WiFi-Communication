#ifndef WIFI4SIMULATOR_H
#define WIFI4SIMULATOR_H

#include "../core/Simulator.h"
#include <string>

class WiFi4Simulator : public Simulator {
private:
    std::string generateRunLog(int runNumber, double &currentTime);

public:
    WiFi4Simulator(int numUsers, int bandwidth);
    void runSimulation() override;
    void runSimulationMultipleTimes(int numIterations);
};

#endif
