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

public:
    // Constructor
    User(int id);

    // Getters
    int getId() const;
    double getBackoffTime() const;
    double getStartTime() const;
    double getEndTime() const;

    // Setters
    void setBackoffTime(double time);
    void setStartTime(double time);
    void setEndTime(double time);

    // Utility functions
    void assignBackoff();
    void transmit(double &currentTime, double transmissionTime);

    // Debugging
    void logTransmission(std::ostream &out) const;
};

#endif
