#include "../../include/core/AccessPoint.h"

AccessPoint::AccessPoint(int id, int frequency)
    : id(id), frequencyChannel(frequency) {}

int AccessPoint::getId() const {
    return id;
}

int AccessPoint::getFrequency() const {
    return frequencyChannel.getBandwidth();
}

void AccessPoint::setFrequency(int freq) {
    frequencyChannel.setBandwidth(freq);
}
