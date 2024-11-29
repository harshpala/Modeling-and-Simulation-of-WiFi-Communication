#include "../../include/core/Packet.h"

// Template method definitions
template <typename SizeType>
Packet<SizeType>::Packet(SizeType size) : size(size) {}

template <typename SizeType>
SizeType Packet<SizeType>::getSize() const {
    return size;
}

template <typename SizeType>
void Packet<SizeType>::setSize(SizeType newSize) {
    size = newSize;
}

// Explicit instantiation
template class Packet<size_t>;