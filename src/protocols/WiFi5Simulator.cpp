#include "../../include/protocols/WiFi5Simulator.h"
#include "../../include/core/User.h"
#include "../../include/core/AccessPoint.h"
#include "../../include/core/Packet.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>  // For stringstream logging

WiFi5Simulator::WiFi5Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth) {}

void WiFi5Simulator::runSimulation(int totalPackets, int numPacketsPerUser) {
    std::cout << "WiFi 5 MU-MIMO Simulation\n";

    // Simulation parameters
    double currentTime = 0.0;
    double broadcastTime = Config::TRANSMISSION_TIME;          // 1 KB broadcast packet transmission time (ms)
    double csiTime = 0.012;                                    // CSI packet transmission time (ms)
    double packetTransmissionTime = Config::TRANSMISSION_TIME; // Data packet transmission time (ms)
    double timeSlot = 15.0;                                    // Time slot for parallel communication (ms)

    // Initialize packetsRemaining vector to track each user's packets
    packetsRemaining.resize(numUsers, numPacketsPerUser); // Packets left for each user

    int packetsSent = 0;  // Count of sent packets

    // Create log stream
    std::ostringstream logStream;
    logStream << "Simulation Details:\n";
    logStream << "---------------------\n";
    logStream << "Number of users: " << numUsers << "\n";
    logStream << "Packets per user: " << numPacketsPerUser << "\n";
    logStream << "Total packets: " << totalPackets << "\n";
    logStream << "Broadcast time: " << broadcastTime << " ms\n";
    logStream << "CSI time: " << csiTime << " ms\n";
    logStream << "Packet transmission time: " << packetTransmissionTime << " ms\n";
    logStream << "Parallel time slot: " << timeSlot << " ms\n";
    logStream << "---------------------\n";

    while (packetsSent < totalPackets) {
        // Step 1: Broadcast a packet
        logStream << "Broadcasting a packet...\n";
        currentTime += broadcastTime;
        logStream << "Broadcast complete. Current time: " << currentTime << " ms.\n";

        // Step 2: Collect CSI packets sequentially from each user
        logStream << "Collecting CSI packets from users...\n";
        for (int i = 0; i < numUsers; ++i) {
            currentTime += csiTime;
            logStream << "User " << i + 1 << " sent CSI at time " << currentTime << " ms.\n";
        }

        // Step 3: Start parallel transmission for the time slot
        double slotStart = currentTime;
        logStream << "Starting parallel transmission for " << timeSlot << " ms...\n";
        for (int i = 0; i < numUsers; ++i) {
            while (packetsRemaining[i] > 0) {
                double transmissionEndTime = currentTime + packetTransmissionTime;

                // If the transmission exceeds the time slot, break
                if (transmissionEndTime > slotStart + timeSlot) {
                    logStream << "User " << i + 1 << " exceeded time slot, ending transmission at time "
                              << currentTime << " ms.\n";
                    break;
                }

                // Send the packet
                packetsRemaining[i]--;
                packetsSent++;
                currentTime = transmissionEndTime;
                latencies.push_back(currentTime);  // Record latency
                timestamps.push_back(currentTime); // Record timestamp

                logStream << "User " << i + 1 << " transmitted a packet at time " << currentTime << " ms.\n";
            }
        }
    }

    // Log the final results
    logStream << "Simulation Complete:\n";
    logStream << "---------------------\n";
    logStream << "Throughput: " << calculateThroughput(totalPackets, currentTime) << " Mbps\n";
    logStream << "Average Latency: " << calculateAverageLatency() << " ms\n";
    logStream << "Max Latency: " << calculateMaxLatency() << " ms\n";
    
    // Save the log to a file
    saveResultsToFile("./logs/wiFi5_simulation_log.txt", logStream.str());

    // Display simulation results
    std::cout << "Simulation Complete:\n";
    std::cout << "Throughput: " << calculateThroughput(totalPackets, currentTime) << " Mbps\n";
    std::cout << "Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}


double WiFi5Simulator::calculateThroughput(int totalPackets, double totalTime) {
    if (totalTime <= 0.0) {
        return 0.0;
    }
    
    // Convert total data to bits: each packet size is in KB, so multiply by 8 to get bits
    double totalDataInBits = totalPackets * Config::PACKET_SIZE_KB * 1024 * 8;  // Convert KB to bits

    // Convert totalTime from milliseconds to seconds
    double totalTimeInSeconds = totalTime / 1000.0;

    // Calculate throughput in Mbps
    return (totalDataInBits / totalTimeInSeconds) / 1e6;  // Convert from bits per second to Mbps
}


double WiFi5Simulator::calculateAverageLatency() {
    if (latencies.empty()) {
        return 0.0;
    }
    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi5Simulator::calculateMaxLatency() {
    if (latencies.empty()) {
        return 0.0;
    }
    return *std::max_element(latencies.begin(), latencies.end());
}
