#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "Config.h"
#include "FrequencyChannel.h"
class AccessPoint {
private:
    int id;
    FrequencyChannel frequencyChannel;

public:
    AccessPoint(int id, int frequency = Config::BANDWIDTH_MHZ);
    
    int getId() const;
    int getFrequency() const;

    // Setters
    void setFrequency(int freq);
};

#endif // ACCESSPOINT_H
