#include <iostream>
#include "../../include/protocols/WiFi6Simulator.h"

int main() {
    try {
        int numUsers;
        std::cout << "Enter the number of users: ";
        std::cin >> numUsers;

        WiFi6Simulator simulator(numUsers, 20);  // 20 MHz bandwidth for WiFi 6
        simulator.runSimulation();  // No need to pass totalPackets or numPacketsPerUser

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
