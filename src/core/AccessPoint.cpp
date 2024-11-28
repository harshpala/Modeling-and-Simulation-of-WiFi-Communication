#include "../../include/core/AccessPoint.h"

AccessPoint::AccessPoint(int id, double frequency)
    : id(id), frequency(frequency) {}

int AccessPoint::getId() const {
    return id;
}

double AccessPoint::getFrequency() const {
    return frequency;
}

void AccessPoint::setFrequency(double freq) {
    frequency = freq;
}
