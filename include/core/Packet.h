#ifndef PACKET_H
#define PACKET_H
#include <cstddef>  // Include this header to use size_t


class Packet {
private:
    size_t size;  // In bytes

public:
    Packet(size_t size = 1024);  // Default to 1 KB

    size_t getSize() const;
    void setSize(size_t newSize);
};

#endif // PACKET_H
