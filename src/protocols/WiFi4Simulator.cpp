#include "../../include/protocols/WiFi4Simulator.h"
#include "../../include/core/User.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>

WiFi4Simulator::WiFi4Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

void WiFi4Simulator::runSimulation() {
    throw std::runtime_error("Single run is not supported directly. Use runSimulationMultipleTimes.");
}

std::string WiFi4Simulator::generateRunLog(int runNumber, double &currentTime) {
    std::ostringstream logStream;
    logStream << "Run " << runNumber << ":\n";
    logStream << "------------------\n";

    const double transmissionTime = 0.0614; // Transmission time for 1 KB packet
    std::vector<User> users;

    // Step 1: Create users and assign initial backoff times
    for (int i = 0; i < numUsers; ++i) {
        User user(i);
        if (i > 0) {
            user.assignBackoff(); // Skip backoff for User 0
        }
        logStream << "User " << user.getId() << " assigned initial backoff: " << user.getBackoffTime() << " ms.\n";
        users.push_back(user);
    }

    // Step 2: Process transmissions dynamically
    while (!users.empty()) {
        // Sort users by their current backoff times
        std::sort(users.begin(), users.end(), [](const User &a, const User &b) {
            return a.getBackoffTime() < b.getBackoffTime();
        });

        User &currentUser = users[0];

        // Update start time based on the channel's current state
        currentUser.setStartTime(std::max(currentTime, currentUser.getBackoffTime()));

        // Check for conflicts
        bool conflictDetected = false;
        for (size_t i = 1; i < users.size(); ++i) {
            if (users[i].getBackoffTime() == currentUser.getBackoffTime()) {
                conflictDetected = true;

                // Assign a new backoff time to the conflicted user
                double oldBackoff = users[i].getBackoffTime();
                users[i].assignBackoff();
                logStream << "Conflict detected for User " << users[i].getId()
                          << " (backoff: " << oldBackoff << " ms). New backoff: "
                          << users[i].getBackoffTime() << " ms.\n";
            }
        }

        if (!conflictDetected) {
            // No conflicts, proceed with transmission
            currentUser.setEndTime(currentUser.getStartTime() + transmissionTime);
            currentTime = currentUser.getEndTime();

            latencies.push_back(currentUser.getEndTime());
            timestamps.push_back(currentUser.getEndTime());

            currentUser.logTransmission(logStream);

            // Remove the user from the list
            users.erase(users.begin());
        }
    }

    return logStream.str();
}

void WiFi4Simulator::runSimulationMultipleTimes(int numIterations) {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::ostringstream fullLog;
    fullLog << "WiFi 4 Simulation Logs\n";
    fullLog << "=========================\n\n";

    std::vector<double> throughputResults;
    std::vector<double> avgLatencyResults;
    std::vector<double> maxLatencyResults;

    for (int run = 1; run <= numIterations; ++run) {
        latencies.clear();
        timestamps.clear();
        double currentTime = 0.0;

        fullLog << "Starting Run " << run << "...\n";
        std::string runLog = generateRunLog(run, currentTime);
        fullLog << runLog;

        if (latencies.empty()) {
            fullLog << "Error: No transmissions occurred in Run " << run << ".\n";
            continue;
        }

        double throughput = calculateThroughput();
        double avgLatency = calculateAverageLatency();
        double maxLatency = calculateMaxLatency();

        throughputResults.push_back(throughput);
        avgLatencyResults.push_back(avgLatency);
        maxLatencyResults.push_back(maxLatency);

        fullLog << "\nResults for Run " << run << ":\n";
        fullLog << "Throughput: " << throughput << " Mbps\n";
        fullLog << "Average Latency: " << avgLatency << " ms\n";
        fullLog << "Max Latency: " << maxLatency << " ms\n\n";
    }

    if (throughputResults.empty()) {
        fullLog << "Error: No data collected across all iterations.\n";
        saveResultsToFile("WiFi4SimulationLogs.txt", fullLog.str());
        std::cerr << "Error: No data collected across all iterations.\n";
        return;
    }

    double avgThroughput = std::accumulate(throughputResults.begin(), throughputResults.end(), 0.0) / numIterations;
    double avgAvgLatency = std::accumulate(avgLatencyResults.begin(), avgLatencyResults.end(), 0.0) / numIterations;
    double avgMaxLatency = std::accumulate(maxLatencyResults.begin(), maxLatencyResults.end(), 0.0) / numIterations;

    fullLog << "\nFinal Averaged Results:\n";
    fullLog << "------------------------\n";
    fullLog << "Average Throughput: " << avgThroughput << " Mbps\n";
    fullLog << "Average Latency: " << avgAvgLatency << " ms\n";
    fullLog << "Maximum Latency: " << avgMaxLatency << " ms\n";

    saveResultsToFile("./logs/simulationLogs.txt", fullLog.str());

    std::cout << "\nFinal Averaged Results:\n";
    std::cout << "Average Throughput: " << avgThroughput << " Mbps\n";
    std::cout << "Average Latency: " << avgAvgLatency << " ms\n";
    std::cout << "Maximum Latency: " << avgMaxLatency << " ms\n";
}
