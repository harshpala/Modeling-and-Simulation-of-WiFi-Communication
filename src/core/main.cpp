#include <iostream>
#include <stdexcept>
#include <limits> // For numeric_limits
#include "../../include/core/Simulator.h"
#include "../../include/protocols/WiFi4Simulator.h"
#include "../../include/protocols/WiFi5Simulator.h"
#include "../../include/protocols/WiFi6Simulator.h"
#include "../../include/core/config.h"

void showMenu() {
    std::cout << "\n===============================================\n";
    std::cout << "        WiFi Simulation Program\n";
    std::cout << "===============================================\n";
    std::cout << "1. WiFi 4 (CSMA/CA)\n";
    std::cout << "2. WiFi 5 (MU-MIMO)\n";
    std::cout << "3. WiFi 6 (OFDMA)\n";
    std::cout << "4. Exit\n";
    std::cout << "===============================================\n";
    std::cout << "Enter your choice (1/2/3/4): ";
}

// Function to handle invalid input with exception
void handleInvalidInput(const std::string& errorMsg) {
    std::cerr << errorMsg << "\n";
    std::cin.clear(); // Clear the error flag on cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the incorrect input
    exit(1);  // Exit the program immediately
}

int main() {
    try {
        bool running = true;  // Flag to control the main loop

        while (running) {
            int choice;
            showMenu();  // Display the main menu

            // Try to read the choice input
            std::cin >> choice;

            if (!std::cin) {
                // Invalid input detected
                handleInvalidInput("Invalid choice! Please enter a number (1/2/3/4).");
            }

            if (choice == 4) {
                std::cout << "Exiting the program. Goodbye!\n";
                running = false;  // Exit the loop and terminate the program
            } 
            else if (choice == 1) {
                // Handle WiFi 4 (CSMA/CA)
                int numUsers, numIterations;
                std::cout << "Enter the number of users (positive integer): ";
                std::cin >> numUsers;

                if (!std::cin || numUsers <= 0) {
                    handleInvalidInput("Error: Number of users must be a positive integer.");
                }

                std::cout << "Enter the number of iterations for averaging results: ";
                std::cin >> numIterations;

                if (!std::cin || numIterations <= 0) {
                    handleInvalidInput("Error: Number of iterations must be a positive integer.");
                }

                WiFi4Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
                simulator.runSimulation(numIterations);  // Run multiple simulations for averaging

            } 
            else if (choice == 2) {
                // Handle WiFi 5 (MU-MIMO)
                int numUsers, numPacketsPerUser;
                std::cout << "Enter the number of users (positive integer): ";
                std::cin >> numUsers;

                if (!std::cin || numUsers <= 0) {
                    handleInvalidInput("Error: Number of users must be a positive integer.");
                }

                std::cout << "Enter the total number of packets per user: ";
                std::cin >> numPacketsPerUser;

                if (!std::cin || numPacketsPerUser <= 0) {
                    handleInvalidInput("Error: Number of packets per user must be a positive integer.");
                }

                int totalPackets = numUsers * numPacketsPerUser;  // Calculate total packets

                WiFi5Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
                simulator.runSimulation(totalPackets, numPacketsPerUser);  // Run simulation for WiFi 5 (MU-MIMO)

            } 
            else if (choice == 3) {
                // Handle WiFi 6 (OFDMA)
                int numUsers;
                std::cout << "Enter the number of users: ";
                std::cin >> numUsers;

                if (!std::cin || numUsers <= 0) {
                    handleInvalidInput("Error: Number of users must be a positive integer.");
                }

                WiFi6Simulator simulator(numUsers, Config::BANDWIDTH_MHZ);  // Use bandwidth from config
                simulator.runSimulation();  // No need to pass totalPackets or numPacketsPerUser
            }
            else {
                // Invalid choice input, exit
                handleInvalidInput("Error: Invalid choice. Please enter 1 for WiFi 4, 2 for WiFi 5, or 3 for WiFi 6.");
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "An unexpected error occurred.\n";
        return 1;
    }

    return 0;
}
