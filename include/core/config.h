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

    // Simulation Control
    constexpr bool IGNORE_GUARD_INTERVALS = true;   // Ignore DIFS, CIFS, and guard intervals

    // WiFi 5 (MU-MIMO) Simulation Parameters
    constexpr double CSI_PACKET_TIME = 0.012;       // CSI packet transmission time (ms)
    constexpr double TIME_SLOT_MS = 15.0;           // Parallel transmission time slot (ms)
}

#endif // CONFIG_H
