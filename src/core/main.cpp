#include <iostream>
#include <stdexcept>
#include "../../include/core/Simulator.h"
#include "../../include/protocols/WiFi4Simulator.h"
#include "../../include/protocols/WiFi5Simulator.h"
#include "../../include/core/config.h"

int main() {
    // Menu to choose WiFi 4 or WiFi 5 simulation
    int choice;
    std::cout << "Select WiFi Simulation Type:\n";
    std::cout << "1. WiFi 4 (CSMA/CA)\n";
    std::cout << "2. WiFi 5 (MU-MIMO)\n";
    std::cout << "Enter your choice (1/2): ";
    std::cin >> choice;

    // Handle WiFi 4 (CSMA/CA)
    if (choice == 1) {
        int numUsers, numIterations;
        std::cout << "Enter the number of users (positive integer): ";
        std::cin >> numUsers;

        if (numUsers <= 0) {
            std::cerr << "Error: Number of users must be a positive integer.\n";
            return 1;
        }

        std::cout << "Enter the number of iterations for averaging results: ";
        std::cin >> numIterations;

        if (numIterations <= 0) {
            std::cerr << "Error: Number of iterations must be a positive integer.\n";
            return 1;
        }

        WiFi4Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
        simulator.runSimulation(numIterations);  // Run multiple simulations for averaging

    } 
    // Handle WiFi 5 (MU-MIMO)
    else if (choice == 2) {
        int numUsers, numPacketsPerUser;
        std::cout << "Enter the number of users (positive integer): ";
        std::cin >> numUsers;

        if (numUsers <= 0) {
            std::cerr << "Error: Number of users must be a positive integer.\n";
            return 1;
        }

        std::cout << "Enter the total number of packets per user: ";
        std::cin >> numPacketsPerUser;

        if (numPacketsPerUser <= 0) {
            std::cerr << "Error: Number of packets per user must be a positive integer.\n";
            return 1;
        }

        int totalPackets = numUsers * numPacketsPerUser;  // Calculate total packets

        WiFi5Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
        simulator.runSimulation(totalPackets, numPacketsPerUser);  // Run simulation for WiFi 5 (MU-MIMO)

    } 
    // Invalid option
    else {
        std::cerr << "Error: Invalid choice. Please enter 1 for WiFi 4 or 2 for WiFi 5.\n";
        return 1;
    }

    return 0;
}
