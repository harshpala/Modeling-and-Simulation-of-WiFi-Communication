# Modeling and Simulation of WiFi Communication
# WiFi 4 Communication ( CSMA/CA)

## Objective
The goal of this project is to simulate WiFi communication protocols, specifically WiFi 4 (CSMA/CA) and WiFi 5 (MU-MIMO). The simulation models communication between multiple users and an Access Point (AP), including processes like packet transmission, backoff time handling, and interference resolution. The simulation calculates throughput, latency, and maximum latency for different scenarios and provides insights into how the protocols perform under various network conditions.

## Approach

- **WiFi 4 Simulation (CSMA/CA)**: 
  In WiFi 4, communication happens via a single AP and a set of users. CSMA/CA is used to determine if the channel is idle or busy before transmitting a packet. If the channel is busy, the transmission is deferred by a random backoff time with collision detection and handling, which is recalculated each time the channel is accessed. The goal is to simulate multiple users and compute throughput and latency metrics.

## Requirements

- **C++17** or higher
- **g++ compiler** (or any C++17 compatible compiler)
- **make** (optional, for building the project easily)

## Code Files

- **WiFi4Simulator.h / WiFi4Simulator.cpp**:
  
  Contains the simulation logic for WiFi 4 (CSMA/CA). It models users, access points, packet transmission, and backoff handling.

- **Simulator.h / Simulator.cpp**:
  
  Abstract base class for simulation, handling shared functionality like throughput and latency calculations, and saving logs.

- **User.h / User.cpp**:
  
  Models the users in the simulation. Each user has properties like backoff time, transmission start and end times, and can transmit data.

- **Packet.h / Packet.cpp**:

  Models the packets in the simulation. It provides the structure for packet size and other related properties.

- **AccessPoint.h / AccessPoint.cpp**:
  
  Models the access point in the simulation. It handles broadcast packet transmissions and communication with users.

- **FrequencyChannel.h / FrequencyChannel.cpp**:
  
  Models the communication channel, handling interference and ensuring that packets are transmitted without collisions.

  ## How to Build and Run

### **Step 1: bash script files to create the directory and file structures**

use the setup.sh to create the directory and file structures:

```bash
./setup.sh
```
### **Step 2: Compile the Project**

Use the `Makefile` to build the project:

```bash
make debug
```
This will build the debug version of the project. You can also build the optimized version with:
```bash
make release
```
### **Step 3: Run the Program**

Run the program, For example:

```bash
./build/build/WiFiSimulator_debug.exe
```
This will ask for number of users and number of iterations to take average of.

If there's a mistake, the program will display an appropriate message.

### Note:
we are assuming that lower the user number higher the priority or we can say that particular user came first, we do this to resolve conflict between two or more users.

## **Features**
### **Publications Display**
For each queried author, the program will display the following details:

- Title of the publication.
- Venue or Journal where the paper was published.
- Year of publication.
- DOI (if available).
- Volume, Number, and Pages (if available).
- List of Authors and their affiliations (if known).

## OOPD Concepts Used

- **Encapsulation**: Data related to users, packets, and the access point is encapsulated in respective classes like `User`, `Packet`, `AccessPoint`, etc.
  
- **Inheritance**: The `Simulator` class is the base class,`WiFi4Simulator` is derived from it, reusing the common functionality.
  
- **Polymorphism**: The `runSimulation()` function is implemented differently for both WiFi 4 and WiFi 5, using the concept of polymorphism for overriding the base class methods.
  
- **Abstraction**: High-level concepts like packet transmission, backoff handling, and user communication are abstracted through appropriate class methods, making the system modular and easy to extend.

- **Composition**: The `WiFi4Simulator` classes aggregate other objects like `User`, `AccessPoint`, `Packet`, etc., to manage their behavior.

- **Aggregation**: Multiple users and packets are aggregated into lists or vectors to handle multiple instances dynamically.

## File/Folder Structure

```
PROJECT_ROOT
│
├── include/
│   │
│   ├── core/
│   │    ├── config.h               # New config file for global constants
│   │    ├── AccessPoint.h          # New Access Point class header
│   │    ├── FrequencyChannel.h     # Header for Frequency Channel class
│   │    ├── Packet.h               # Header for Packet class
│   │    ├── Simulator.h            # Simulator base class header
│   │    └── User.h                 # User class header
│   └── protocols/
│         └── WiFi4Simulator.cpp    # WiFi 4 Simulator implementation
├── src/
│   │
│   ├── core/
│   │    ├── main.cpp               # Main application entry
│   │    ├── AccessPoint.cpp        # Implementation for Access Point class
│   │    ├── FrequencyChannel.cpp   # Implementation for Frequency Channel class
│   │    ├── Packet.cpp             # Implementation for Packet class
│   │    ├── Simulator.cpp          # Simulator base class implementation
│   │    └── User.cpp               # User class implementation
│   │   
│   └── protocols/
│        └── WiFi4Simulator.cpp     # WiFi 4 Simulator implementation
│
├── assets/                # contains images used in this Readme.md
├── build/                 # Build folder (generated on compilation)
├── logs/                  # Logs folder (generated on running simulation)
├── Makefile               # Makefile for building the project
└── README.md              # This readme file

```

## **Flowchart for CSMA/CA (WiFi 4)**
The CSMA/CA process involves the following steps:

- `Idle Channel`: If the channel is idle, the user transmits immediately.
- `Busy Channel`: If the channel is busy, the user waits for a random backoff time.
- `Backoff`: The user waits for a random amount of time and retries the process.
- `Transmission`: After waiting, the user checks if the channel is idle and transmits the packet else a new backoff time is assigned again.


Below is the flowchart for CSMA/CA:

![CSMA/CA Flowchart](./assets/CSMA_CA_flowchart.gif)

##

## References Used

- **Carrier Sense Multiple Access (CSMA)**:
  - Source: [IONOS-Digital Guide](https://www.ionos.com/digitalguide/server/know-how/csmaca-carrier-sense-multiple-access-with-collision-avoidance/)
  - Source: [GeeksforGeeks](https://www.geeksforgeeks.org/collision-detection-csmacd/)