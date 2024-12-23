#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

#include "config.h"

class FrequencyChannel {
private:
    int bandwidth;  // Bandwidth in MHz

public:
    FrequencyChannel(int bandwidth = Config::BANDWIDTH_MHZ);

    int getBandwidth() const;
    void setBandwidth(int bandwidth);
};

#endif // FREQUENCYCHANNEL_H
