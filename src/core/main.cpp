#include <iostream>
#include <stdexcept>
#include "../../include/core/Simulator.h"
#include "../../include/protocols/WiFi5Simulator.h"

#include <iostream>
#include "../../include/protocols/WiFi5Simulator.h"

int main() {
    // Collect user input
    int numUsers, numPacketsPerUser;
    std::cout << "Enter the number of users: ";
    std::cin >> numUsers;

    std::cout << "Enter the number of packets per user: ";
    std::cin >> numPacketsPerUser;

    int totalPackets = numUsers * numPacketsPerUser;  // Calculate total packets

    WiFi5Simulator simulator(numUsers, 20);  // 20 MHz bandwidth
    simulator.runSimulation(totalPackets, numPacketsPerUser);  // Pass totalPackets and numPacketsPerUser

    return 0;
}

