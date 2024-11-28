#include "../../include/core/FrequencyChannel.h"

FrequencyChannel::FrequencyChannel(double bandwidth)
    : bandwidth(bandwidth) {}

double FrequencyChannel::getBandwidth() const {
    return bandwidth;
}

void FrequencyChannel::setBandwidth(double bandwidth) {
    this->bandwidth = bandwidth;
}
