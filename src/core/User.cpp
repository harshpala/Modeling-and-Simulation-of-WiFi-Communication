#include "../../include/core/User.h"
#include "../../include/core/Config.h"
#include <cstdlib> // For rand()

User::User(int id, int totalPackets) : id(id), backoffTime(0.0), startTime(0.0), endTime(0.0), totalPackets(totalPackets) {}

int User::getId() const {
    return id;
}

double User::getBackoffTime() const {
    return backoffTime;
}

double User::getStartTime() const {
    return startTime;
}

double User::getEndTime() const {
    return endTime;
}

int User::getTotalPackets() const {
    return totalPackets;  // Return total packets
}

void User::setBackoffTime(double time) {
    backoffTime = time;
}

void User::setStartTime(double time) {
    startTime = time;
}

void User::setEndTime(double time) {
    endTime = time;
}

void User::setTotalPackets(int packets) {
    totalPackets = packets;  // Set total packets for the user
}

void User::assignBackoff() {
    backoffTime = rand() % Config::MAX_BACKOFF_MS + Config::MIN_BACKOFF_MS; // Random backoff between 1-10 ms
}

void User::transmit(double &currentTime, double transmissionTime) {
    startTime = std::max(currentTime, backoffTime);
    endTime = startTime + transmissionTime;
    currentTime = endTime;
}

void User::logTransmission(std::ostream &out) const {
    out << "User " << id << " waiting (backoff: " << backoffTime
        << " ms, current time: " << std::fixed << std::setprecision(4) << startTime - backoffTime << " ms).\n";
    out << "User " << id << " transmitted at time " << std::fixed
        << std::setprecision(4) << endTime << " ms.\n";
}
