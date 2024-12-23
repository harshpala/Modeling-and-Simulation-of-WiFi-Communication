#include "../../include/core/Config.h"
#include "../../include/protocols/WiFi4Simulator.h"
#include "../../include/core/User.h"
#include "../../include/core/AccessPoint.h"
#include "../../include/core/Packet.h"
#include "../../include/core/FrequencyChannel.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>

WiFi4Simulator::WiFi4Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

std::string WiFi4Simulator::generateRunLog(int runNumber, double &currentTime) {
    std::ostringstream logStream;
    logStream << "Run " << runNumber << ":\n";
    logStream << "------------------\n";

    const double transmissionTime = Config::TRANSMISSION_TIME;  // Use Config constant
    std::vector<User> users;

    // Step 1: Create users and assign initial backoff times
    for (int i = 1; i <= numUsers; ++i) {
        User user(i);
        if (i > 1) {
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

        // Create a packet for the current user (1 KB by default)
        Packet<size_t> packet(Config::PACKET_SIZE_KB);  // Create a packet object with size from Config

        // Update start time based on the channel's current state
        currentUser.setStartTime(std::max(currentTime, currentUser.getBackoffTime()));

        // Check for conflicts
        bool conflictDetected = false;
        for (size_t i = 1; i < users.size(); ++i) {
            if (users[i].getBackoffTime() == currentUser.getBackoffTime()) {
                conflictDetected = true;

                // Assign a new backoff time to the conflicted user
                double oldBackoff = users[i].getBackoffTime();
                double originalArrivalTime = std::max(currentTime, oldBackoff);
                users[i].assignBackoff();
                double newArrivalTime = originalArrivalTime + users[i].getBackoffTime();

                logStream << "Conflict detected for User " << users[i].getId()
                          << " (backoff: " << oldBackoff << " ms). New backoff: "
                          << users[i].getBackoffTime() << " ms. User will now arrive at "
                          << std::fixed << std::setprecision(4) << newArrivalTime << " ms.\n";

                // Update the user's backoff time and re-sort the list
                users[i].setBackoffTime(newArrivalTime);
            }
        }

        // Re-sort users after conflict resolution if needed
        if (conflictDetected) {
            std::sort(users.begin(), users.end(), [](const User &a, const User &b) {
                return a.getBackoffTime() < b.getBackoffTime();
            });
            continue; // Skip processing for this iteration and re-check conflicts
        }

        // No conflicts, proceed with transmission
        currentUser.setEndTime(currentUser.getStartTime() + transmissionTime);
        currentTime = currentUser.getEndTime();  // Update the global currentTime

        latencies.push_back(currentUser.getEndTime());
        timestamps.push_back(currentUser.getEndTime());

        // Log the transmission, including the packet size
        logStream << "User " << currentUser.getId()
                  << " waiting (backoff: " << currentUser.getBackoffTime()
                  << " ms, current time: " << std::fixed << std::setprecision(4) << currentUser.getStartTime() << " ms).\n";
        logStream << "User " << currentUser.getId() << " transmitted a "
                  << packet.getSize() << " KB packet at time "
                  << std::fixed << std::setprecision(4) << currentUser.getEndTime() << " ms.\n";

        // Remove the user from the list after transmission
        users.erase(users.begin());
    }

    return logStream.str();
}



void WiFi4Simulator::runSimulation(int numIterations) {
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
        saveResultsToFile("./logs/wifi_4_simulation_log.txt", fullLog.str());
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

    saveResultsToFile("./logs/wifi_4_simulation_log.txt", fullLog.str());

    std::cout << "\nFinal Averaged Results:\n";
    std::cout << "Average Throughput: " << avgThroughput << " Mbps\n";
    std::cout << "Average Latency: " << avgAvgLatency << " ms\n";
    std::cout << "Maximum Latency: " << avgMaxLatency << " ms\n";
}
