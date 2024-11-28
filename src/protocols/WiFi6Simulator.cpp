#include "../../include/protocols/WiFi6Simulator.h"
#include "../../include/core/User.h"
#include "../../include/core/AccessPoint.h"
#include "../../include/core/Packet.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <cmath>  // For log function
#include "../../include/core/Config.h"  // Include Config.h for global settings

WiFi6Simulator::WiFi6Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth), subChannelWidth(4), numPacketsPerUser(1) {}  // Default sub-channel width set to 4 MHz

double WiFi6Simulator::calculateThroughput()
{
    if (latencies.empty())
        return 0.0;

    double totalData = latencies.size() * 8192.0;    // Total data in bits (1 KB = 8192 bits)
    double totalTime = timestamps.back();            // Total simulation time in ms
    return (totalData / (totalTime / 1000.0)) / 1e6; // Throughput in Mbps
}

void WiFi6Simulator::runSimulation()
{
    std::cout << "\n--- WiFi 6 OFDMA Simulation ---\n";

    // Ask the user for sub-channel width
    int userInputSubChannelWidth;
    std::cout << "Enter sub-channel width (2, 4, or 10 MHz): ";
    std::cin >> userInputSubChannelWidth;

    // Validate sub-channel width
    if (userInputSubChannelWidth != 2 && userInputSubChannelWidth != 4 && userInputSubChannelWidth != 10)
    {
        throw std::invalid_argument("Invalid sub-channel width! Only 2, 4, or 10 MHz are allowed.");
    }
    subChannelWidth = userInputSubChannelWidth;

    int numSubChannels = bandwidth / subChannelWidth;                            // Calculate sub-channels based on total bandwidth
    double dataRatePerSubChannel = (Config::DATA_RATE_MBPS * subChannelWidth) / 20.0; // Mbps per sub-channel
    double transmissionTime = (8192.0 / (dataRatePerSubChannel * 1e6)) * 1000.0; // ms for 1 KB

    if (dataRatePerSubChannel <= 0)
    {
        std::cerr << "Error: Data rate per sub-channel is invalid. Exiting simulation.\n";
        return;
    }

    std::cout << "Total Bandwidth: " << bandwidth << " MHz\n";
    std::cout << "Sub-channel Width: " << subChannelWidth << " MHz\n";
    std::cout << "Number of Sub-channels: " << numSubChannels << "\n";
    std::cout << "Transmission Time per Packet: " << std::fixed << std::setprecision(4) << transmissionTime << " ms\n\n";

    latencies.clear();
    timestamps.clear();

    int remainingUsers = numUsers;
    double currentTime = 0.0;

    // Main simulation loop for sending packets
    while (remainingUsers > 0)
    {
        std::cout << "--- Starting Frame at " << currentTime << " ms ---\n";

        // Assign users to sub-channels based on the sub-channel width and remaining users
        int usersThisFrame = std::min(numSubChannels, remainingUsers);

        for (int i = 0; i < usersThisFrame; ++i)
        {
            int user = numUsers - remainingUsers + i;
            double latency = currentTime + transmissionTime;

            timestamps.push_back(latency);
            latencies.push_back(latency);

            std::cout << "User " << user + 1 << " transmits at " << std::fixed << std::setprecision(4) << latency << " ms on " << subChannelWidth << " MHz channel\n";
        }

        remainingUsers -= usersThisFrame;
        currentTime += 5.0; // Move to the next frame (frame duration is 5 ms)
    }

    // Display simulation results
    std::cout << "\nSimulation Results:\n";
    std::cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    std::cout << "Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}

double WiFi6Simulator::calculateAverageLatency()
{
    if (latencies.empty())
        return 0.0;

    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi6Simulator::calculateMaxLatency()
{
    if (latencies.empty())
        return 0.0;

    return *std::max_element(latencies.begin(), latencies.end());
}
