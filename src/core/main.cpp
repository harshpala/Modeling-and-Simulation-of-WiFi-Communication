#include <iostream>
#include <stdexcept>
#include "../../include/core/Simulator.h"
#include "../../include/protocols/WiFi4Simulator.h"
#include "../../include/protocols/WiFi5Simulator.h"
#include "../../include/protocols/WiFi6Simulator.h"  // Include WiFi 6 simulator
#include "../../include/core/config.h"

int main() {
    try {
        int choice;

        // Menu to select WiFi simulation type
        std::cout << "Select WiFi Simulation Type:\n";
        std::cout << "1. WiFi 4 (CSMA/CA)\n";
        std::cout << "2. WiFi 5 (MU-MIMO)\n";
        std::cout << "3. WiFi 6 (OFDMA)\n";  // Added option for WiFi 6
        std::cout << "Enter your choice (1/2/3): ";
        std::cin >> choice;

        // Handle WiFi 4 (CSMA/CA)
        if (choice == 1) {
            int numUsers, numIterations;
            std::cout << "Enter the number of users (positive integer): ";
            std::cin >> numUsers;

            if (numUsers <= 0) {
                throw std::invalid_argument("Error: Number of users must be a positive integer.");
            }

            std::cout << "Enter the number of iterations for averaging results: ";
            std::cin >> numIterations;

            if (numIterations <= 0) {
                throw std::invalid_argument("Error: Number of iterations must be a positive integer.");
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
                throw std::invalid_argument("Error: Number of users must be a positive integer.");
            }

            std::cout << "Enter the total number of packets per user: ";
            std::cin >> numPacketsPerUser;

            if (numPacketsPerUser <= 0) {
                throw std::invalid_argument("Error: Number of packets per user must be a positive integer.");
            }

            int totalPackets = numUsers * numPacketsPerUser;  // Calculate total packets

            WiFi5Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
            simulator.runSimulation(totalPackets, numPacketsPerUser);  // Run simulation for WiFi 5 (MU-MIMO)
        } 
        // Handle WiFi 6 (OFDMA)
        else if (choice == 3) {
            int numUsers;
            std::cout << "Enter the number of users: ";
            std::cin >> numUsers;

            if (numUsers <= 0) {
                throw std::invalid_argument("Error: Number of users must be a positive integer.");
            }

            WiFi6Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
            simulator.runSimulation();  // No need to pass totalPackets or numPacketsPerUser
        }
        // Invalid option
        else {
            throw std::invalid_argument("Error: Invalid choice. Please enter 1 for WiFi 4, 2 for WiFi 5, or 3 for WiFi 6.");
        }
    } catch (const std::invalid_argument &e) {
        std::cerr << "Input error: " << e.what() << '\n';
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "An unexpected error occurred.\n";
        return 1;
    }

    return 0;
}
