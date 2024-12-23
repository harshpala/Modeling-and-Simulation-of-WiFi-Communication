#ifndef PACKET_H
#define PACKET_H
#include <cstddef>  // Include this header to use size_t

template <typename SizeType = size_t>
class Packet {
private:
    SizeType size;  // Size in bytes or other units

public:
    explicit Packet(SizeType size = 1024);
    SizeType getSize() const;
    void setSize(SizeType newSize);
};

// Declare explicit instantiations
extern template class Packet<size_t>;

#endif // PACKET_H