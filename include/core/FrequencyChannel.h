#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

#include "config.h"

class FrequencyChannel {
private:
    double bandwidth;  // Bandwidth in MHz

public:
    FrequencyChannel(double bandwidth = Config::BANDWIDTH_MHZ);

    double getBandwidth() const;
    void setBandwidth(double bandwidth);
};

#endif // FREQUENCYCHANNEL_H
