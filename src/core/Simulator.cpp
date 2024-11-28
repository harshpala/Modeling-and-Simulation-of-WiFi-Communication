#include "../../include/core/Simulator.h"
#include <stdexcept>

Simulator::Simulator(int numUsers, int bandwidth)
    : numUsers(numUsers), bandwidth(bandwidth) {}

double Simulator::calculateThroughput() {
    if (timestamps.empty()) return 0.0;
    double totalData = timestamps.size() * 8192.0; // 1 KB = 8192 bits
    double totalTime = timestamps.back() / 1000.0; // Convert ms to seconds
    return (totalTime > 0) ? (totalData / totalTime) / 1e6 : 0.0; // Mbps
}

double Simulator::calculateAverageLatency() {
    if (latencies.empty()) return 0.0;
    return std::accumulate(latencies.begin(), latencies.end(), 0.0) / latencies.size();
}

double Simulator::calculateMaxLatency() {
    if (latencies.empty()) return 0.0;
    return *std::max_element(latencies.begin(), latencies.end());
}

void Simulator::saveResultsToFile(const std::string &filename, const std::string &logData) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    file << logData;
    file.close();
}
