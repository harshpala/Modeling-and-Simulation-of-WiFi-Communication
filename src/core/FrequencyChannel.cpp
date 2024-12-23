#include "../../include/core/FrequencyChannel.h"

FrequencyChannel::FrequencyChannel(int bandwidth)
    : bandwidth(bandwidth) {}

int FrequencyChannel::getBandwidth() const {
    return bandwidth;
}

void FrequencyChannel::setBandwidth(int bandwidth) {
    this->bandwidth = bandwidth;
}
