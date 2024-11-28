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
    std::cout << totalDataInBits << "/" << totalTimeInSeconds << "=" << totalDataInBits/totalTimeInSeconds << "\n;";
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

    // Calculate CSI time dynamically based on sub-channel frequency using the formula
    double csiTime = (1024 * 8) / ((subChannelWidth * log2(Config::MODULATION) * Config::CODING_RATE * 1000));
    std::cout << "CSI Time per User: " << csiTime << " ms\n";

    int numSubChannels = Config::BANDWIDTH_MHZ / subChannelWidth;
    double frameDuration = Config::TIME_SLOT_OFDMA_MS; // Time duration for one transmission frame (ms)

    std::cout << "Sub-channel width: " << subChannelWidth << " MHz.\n";
    std::cout << "Total available sub-channels: " << numSubChannels << ".\n";

    // Ask for the number of packets per user
    std::cout << "Enter the number of packets per user: ";
    std::cin >> numPacketsPerUser;

    double currentTime = 0.0;
    int packetsSent = 0;

    // Track packets remaining for each user
    std::vector<int> packetsRemaining(numUsers, numPacketsPerUser);
    std::vector<bool> usersFinished(numUsers, false); // Track if a user has finished transmitting their packets
    int usersRemaining = numUsers;                    // Track users that still need to transmit

    // Main simulation loop for sending packets
    while (packetsSent < numUsers * numPacketsPerUser)
    {
        int usersInFrame = std::min(usersRemaining, numSubChannels);

        // Step 1: Start parallel transmission (using OFDMA for 5 ms)
        double slotStart = currentTime;
        int currentUserIndex = 0;

        // Round-robin scheduling for the users
        for (int i = 0; i < usersInFrame; ++i)
        {
            // Find the next user with remaining packets
            while (usersRemaining > 0)
            {
                // Skip users who have already finished
                if (packetsRemaining[currentUserIndex] == 0)
                {
                    currentUserIndex = (currentUserIndex + 1) % numUsers;
                    continue;
                }

                double transmissionEndTime = currentTime + csiTime;

                // If transmission exceeds the available time slot, break the inner loop
                if (transmissionEndTime > slotStart + frameDuration)
                {
                    break;
                }

                // Send the packet
                packetsRemaining[currentUserIndex]--;
                packetsSent++;
                std::cout << "Packet number " << packetsSent << "\n";
                currentTime = transmissionEndTime;

                // Track latencies and timestamps
                latencies.push_back(currentTime);  // Record latency
                timestamps.push_back(currentTime); // Record timestamp
                std::cout << "User " << currentUserIndex + 1 << " sent a data packet at " << currentTime << " ms.\n";

                // Mark this user as finished if they have no packets left
                if (packetsRemaining[currentUserIndex] == 0)
                {
                    usersFinished[currentUserIndex] = true;
                    usersRemaining--;
                }

                // Move to the next user in round-robin fashion
                currentUserIndex = (currentUserIndex + 1) % numUsers;

                // Break if all users have finished
                if (usersRemaining == 0)
                {
                    break;
                }
            }

            // Break the outer loop if all users have finished
            if (usersRemaining == 0)
            {
                break;
            }
        }

        // Update the number of remaining users based on those who have finished
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
