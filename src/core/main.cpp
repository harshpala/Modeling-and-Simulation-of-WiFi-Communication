#include <iostream>
#include <stdexcept>
#include "../../include/core/Simulator.h"
#include "../../include/protocols/WiFi4Simulator.h"

int main() {
    try {
        std::cout << "WiFi 4 Simulator (CSMA/CA)\n";

        int numUsers, numIterations;
        std::cout << "Enter the number of users (positive integer): ";
        std::cin >> numUsers;

        if (numUsers <= 0) {
            throw std::invalid_argument("Number of users must be a positive integer.");
        }

        std::cout << "Enter the number of iterations for averaging results: ";
        std::cin >> numIterations;

        if (numIterations <= 0) {
            throw std::invalid_argument("Number of iterations must be a positive integer.");
        }

        const int bandwidth = 20; // 20 MHz bandwidth
        WiFi4Simulator simulator(numUsers, bandwidth);
        simulator.runSimulationMultipleTimes(numIterations);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
