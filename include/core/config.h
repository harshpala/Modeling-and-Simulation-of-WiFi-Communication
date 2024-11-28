#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    // Simulation Assumptions
    constexpr double BANDWIDTH_MHZ = 20.0;          // Bandwidth in MHz
    constexpr double MODULATION = 256.0;            // 256-QAM
    constexpr double CODING_RATE = 5.0 / 6.0;       // Coding rate (5/6)
    constexpr double PACKET_SIZE_KB = 1.0;          // Packet size in KB
    constexpr double TRANSMISSION_TIME = 0.0614;    // Time to transmit 1 KB packet (ms)

    // Random Backoff Configuration
    constexpr int MIN_BACKOFF_MS = 1;               // Minimum backoff time (ms)
    constexpr int MAX_BACKOFF_MS = 10;              // Maximum backoff time (ms)

    // Data Rate
    constexpr double DATA_RATE_MBPS = 133.33;       // Data rate for 256-QAM (Mbps)
    
    // Transmission rate for WiFi 5 (assuming 20 MHz channel and 256-QAM modulation)
    constexpr double TRANSMISSION_RATE = DATA_RATE_MBPS * MODULATION / 256.0; // Mbps

    // Simulation Control
    constexpr bool IGNORE_GUARD_INTERVALS = true;   // Ignore DIFS, CIFS, and guard intervals

    // Number of packets per user
    constexpr int NUM_PACKETS_PER_USER = 5;         // Adjust as needed (for example, each user sends 5 packets)
}

#endif // CONFIG_H
