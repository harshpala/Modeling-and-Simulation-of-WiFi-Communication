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
#include <cmath>                       // For log function
#include "../../include/core/Config.h" // Include Config.h for global settings

WiFi6Simulator::WiFi6Simulator(int numUsers, int bandwidth)
    : Simulator(numUsers, bandwidth), subChannelWidth(4), numPacketsPerUser(1) {} // Default sub-channel width set to 4 MHz, default packets per user set to 1

double WiFi6Simulator::calculateThroughput()
{
    // Total data in bits for throughput calculation
    double totalDataInBits = numUsers * Config::PACKET_SIZE_KB * 1024 * 8 * numPacketsPerUser; // 1 KB = 8 bits

    // Convert totalTime to seconds
    double totalTimeInSeconds = latencies.back() / 1000.0; // Convert last timestamp (latency) to seconds
    std::cout << totalDataInBits << "/" << totalTimeInSeconds << "=" << totalDataInBits/totalTimeInSeconds << "\n";
    if (totalTimeInSeconds <= 0.0)
    {
        return 0.0;
    }

    // Calculate throughput in Mbps (bits per second / 1e6 to convert to Mbps)
    return (totalDataInBits / totalTimeInSeconds) / 1e6;
}

void WiFi6Simulator::runSimulation()
{
    std::cout << "Running WiFi 6 Simulation (OFDMA)...\n";

    int userInputSubChannelWidth;
    std::cout << "Enter sub-channel width (2 MHz, 4 MHz, or 10 MHz): ";
    std::cin >> userInputSubChannelWidth;

    if (userInputSubChannelWidth != 2 && userInputSubChannelWidth != 4 && userInputSubChannelWidth != 10)
    {
        throw std::invalid_argument("Invalid sub-channel width! Use 2, 4, or 10 MHz.");
    }
    subChannelWidth = userInputSubChannelWidth;

    // Calculate channel-specific parameters
    int numSubChannels = Config::BANDWIDTH_MHZ / subChannelWidth;
    double frameDuration = Config::TIME_SLOT_OFDMA_MS; // 5 ms time slot

    // Calculate packets per channel based on sub-channel width
    // Assume different transmission rates for different channel widths
    int packetsPerChannel;
    switch(subChannelWidth) {
        case 2:
            packetsPerChannel = 1; // Narrowest channel, fewer packets
            break;
        case 4:
            packetsPerChannel = 2; // Medium channel width
            break;
        case 10:
            packetsPerChannel = 3; // Widest channel, more packets
            break;
        default:
            packetsPerChannel = 1; // Default fallback
    }

    std::cout << "Sub-channel width: " << subChannelWidth << " MHz.\n";
    std::cout << "Total available sub-channels: " << numSubChannels << ".\n";
    std::cout << "Packets per channel in 5ms: " << packetsPerChannel << ".\n";

    // Ask for the number of packets per user
    std::cout << "Enter the number of packets per user: ";
    std::cin >> numPacketsPerUser;

    double currentTime = 0.0;
    int packetsSent = 0;

    // Track packets remaining for each user
    std::vector<int> packetsRemaining(numUsers, numPacketsPerUser);
    std::vector<bool> usersFinished(numUsers, false);
    int usersRemaining = numUsers;

    // Main simulation loop for sending packets
    while (packetsSent < numUsers * numPacketsPerUser)
    {
        // Determine how many users can transmit in this frame
        int availableChannels = std::min(numSubChannels, usersRemaining);

        // Start of the time slot
        double slotStart = currentTime;
        double slotEnd = slotStart + frameDuration;

        // Track active users for this frame
        std::vector<int> activeUsers;
        for (int i = 0; i < numUsers; ++i)
        {
            if (!usersFinished[i] && packetsRemaining[i] > 0 && activeUsers.size() < availableChannels)
            {
                activeUsers.push_back(i);
            }
        }

        // Transmit packets for active users in this frame
        for (int userIndex : activeUsers)
        {
            // Send packets for this user within the channel capacity
            for (int j = 0; j < packetsPerChannel && packetsRemaining[userIndex] > 0; ++j)
            {
                // Calculate transmission time for each packet
                // double packetTransmissionTime = Config::TRANSMISSION_TIME;
                // correct output
                double packetTransmissionTime = (1024 * 8) / ((subChannelWidth * log2(Config::MODULATION) * Config::CODING_RATE * 1000));;
                // Send a packet for this user
                packetsRemaining[userIndex]--;
                packetsSent++;

                // Update current time
                currentTime += packetTransmissionTime;

                // Track latencies and timestamps
                latencies.push_back(currentTime);
                timestamps.push_back(currentTime);
                
                std::cout << "User " << userIndex + 1 
                          << " sent packet " << packetsSent 
                          << " at " << currentTime << " ms "
                          << "on " << subChannelWidth << " MHz channel\n";

                // Break if time slot is exhausted
                if (currentTime >= slotEnd) break;
            }

            // Mark user as finished if no more packets
            if (packetsRemaining[userIndex] == 0)
            {
                usersFinished[userIndex] = true;
                usersRemaining--;
            }
        }

        // Ensure we move to the next time slot
        currentTime = slotEnd;

        // Update the number of remaining users
        usersRemaining = std::count(usersFinished.begin(), usersFinished.end(), false);
    }

    // Display simulation results
    std::cout << "\nSimulation Complete!\n";
    std::cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    std::cout << "Average Latency: " << calculateAverageLatency() << " ms\n";
    std::cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}

double WiFi6Simulator::calculateAverageLatency()
{
    if (latencies.empty())
    {
        return 0.0;
    }
    double totalLatency = std::accumulate(latencies.begin(), latencies.end(), 0.0);
    return totalLatency / latencies.size();
}

double WiFi6Simulator::calculateMaxLatency()
{
    if (latencies.empty())
    {
        return 0.0;
    }
    return *std::max_element(latencies.begin(), latencies.end());
}
