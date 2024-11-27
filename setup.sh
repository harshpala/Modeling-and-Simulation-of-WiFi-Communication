#!/bin/bash

# Get the directory where the script is located
PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Create directories for organized structure
mkdir -p "$PROJECT_ROOT/src/core" "$PROJECT_ROOT/src/protocols" "$PROJECT_ROOT/src/utils"
mkdir -p "$PROJECT_ROOT/include/core" "$PROJECT_ROOT/include/protocols" "$PROJECT_ROOT/include/utils"
mkdir -p "$PROJECT_ROOT/build" "$PROJECT_ROOT/tests" "$PROJECT_ROOT/logs"

# Create empty source files in respective subfolders
[ ! -f "$PROJECT_ROOT/src/core/main.cpp" ] && touch "$PROJECT_ROOT/src/core/main.cpp"
[ ! -f "$PROJECT_ROOT/src/core/Simulator.cpp" ] && touch "$PROJECT_ROOT/src/core/Simulator.cpp"
[ ! -f "$PROJECT_ROOT/src/core/User.cpp" ] && touch "$PROJECT_ROOT/src/core/User.cpp"
[ ! -f "$PROJECT_ROOT/src/core/AccessPoint.cpp" ] && touch "$PROJECT_ROOT/src/core/AccessPoint.cpp"
[ ! -f "$PROJECT_ROOT/src/utils/Channel.cpp" ] && touch "$PROJECT_ROOT/src/utils/Channel.cpp"
[ ! -f "$PROJECT_ROOT/src/utils/Packet.cpp" ] && touch "$PROJECT_ROOT/src/utils/Packet.cpp"
[ ! -f "$PROJECT_ROOT/src/protocols/WiFi4Simulator.cpp" ] && touch "$PROJECT_ROOT/src/protocols/WiFi4Simulator.cpp"
[ ! -f "$PROJECT_ROOT/src/protocols/WiFi5Simulator.cpp" ] && touch "$PROJECT_ROOT/src/protocols/WiFi5Simulator.cpp"
[ ! -f "$PROJECT_ROOT/src/protocols/WiFi6Simulator.cpp" ] && touch "$PROJECT_ROOT/src/protocols/WiFi6Simulator.cpp"

# Create empty header files in respective subfolders
[ ! -f "$PROJECT_ROOT/include/core/Simulator.h" ] && touch "$PROJECT_ROOT/include/core/Simulator.h"
[ ! -f "$PROJECT_ROOT/include/core/User.h" ] && touch "$PROJECT_ROOT/include/core/User.h"
[ ! -f "$PROJECT_ROOT/include/core/AccessPoint.h" ] && touch "$PROJECT_ROOT/include/core/AccessPoint.h"
[ ! -f "$PROJECT_ROOT/include/utils/Channel.h" ] && touch "$PROJECT_ROOT/include/utils/Channel.h"
[ ! -f "$PROJECT_ROOT/include/utils/Packet.h" ] && touch "$PROJECT_ROOT/include/utils/Packet.h"
[ ! -f "$PROJECT_ROOT/include/protocols/WiFi4Simulator.h" ] && touch "$PROJECT_ROOT/include/protocols/WiFi4Simulator.h"
[ ! -f "$PROJECT_ROOT/include/protocols/WiFi5Simulator.h" ] && touch "$PROJECT_ROOT/include/protocols/WiFi5Simulator.h"
[ ! -f "$PROJECT_ROOT/include/protocols/WiFi6Simulator.h" ] && touch "$PROJECT_ROOT/include/protocols/WiFi6Simulator.h"

# Create empty test files if they do not exist
[ ! -f "$PROJECT_ROOT/tests/test_simulator.cpp" ] && touch "$PROJECT_ROOT/tests/test_simulator.cpp"

# Create logs directory if it does not exist
mkdir -p "$PROJECT_ROOT/logs"

# Print the project structure
echo "Project structure created. Directory and file setup:"
echo "
$PROJECT_ROOT/
│
├── src/
│   ├── core/
│   │   ├── main.cpp        # Main application entry
│   │   ├── Simulator.cpp   # Simulator base class implementation
│   │   ├── User.cpp        # User class implementation
│   │   ├── AccessPoint.cpp # AccessPoint class implementation
│   ├── utils/
│   │   ├── Channel.cpp     # Channel class implementation
│   │   └── Packet.cpp      # Packet class implementation
│   └── protocols/
│       ├── WiFi4Simulator.cpp  # WiFi 4 Simulator implementation
│       ├── WiFi5Simulator.cpp  # WiFi 5 Simulator implementation
│       └── WiFi6Simulator.cpp  # WiFi 6 Simulator implementation
│
├── include/
│   ├── core/
│   │   ├── Simulator.h     # Simulator base class header
│   │   ├── User.h          # User class header
│   │   ├── AccessPoint.h   # AccessPoint class header
│   ├── utils/
│   │   ├── Channel.h       # Channel class header
│   │   └── Packet.h        # Packet class header
│   └── protocols/
│       ├── WiFi4Simulator.h  # WiFi 4 Simulator header
│       ├── WiFi5Simulator.h  # WiFi 5 Simulator header
│       └── WiFi6Simulator.h  # WiFi 6 Simulator header
│
├── build/                  # Directory for build artifacts
│
├── tests/
│   └── test_simulator.cpp  # Test file for simulator
│
└── logs/                   # Directory for logs
"
