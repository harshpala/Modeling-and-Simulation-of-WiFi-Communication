#include "../../include/core/Packet.h"

Packet::Packet(size_t size) : size(size) {}

size_t Packet::getSize() const {
    return size;
}

void Packet::setSize(size_t newSize) {
    size = newSize;
}
