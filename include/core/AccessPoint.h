#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "Config.h"

class AccessPoint {
private:
    int id;
    double frequency;

public:
    AccessPoint(int id, double frequency = Config::BANDWIDTH_MHZ);
    
    int getId() const;
    double getFrequency() const;

    // Setters
    void setFrequency(double freq);
};

#endif // ACCESSPOINT_H
