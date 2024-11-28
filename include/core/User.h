#ifndef USER_H
#define USER_H

#include <iostream>
#include <iomanip>

class User {
private:
    int id;
    double backoffTime;
    double startTime;
    double endTime;
     int totalPackets;  // New member to store the total number of packets

public:
    // Constructor
    User(int id, int totalPackets = 0);

    // Getters
    int getId() const;
    double getBackoffTime() const;
    double getStartTime() const;
    double getEndTime() const;
    int getTotalPackets() const;  // Getter for totalPackets

    // Setters
    void setBackoffTime(double time);
    void setStartTime(double time);
    void setEndTime(double time);
    void setTotalPackets(int packets);  // Setter for totalPackets

    // Utility functions
    void assignBackoff();
    void transmit(double &currentTime, double transmissionTime);

    // Debugging
    void logTransmission(std::ostream &out) const;
};

#endif
