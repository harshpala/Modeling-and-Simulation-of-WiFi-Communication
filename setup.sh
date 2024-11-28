#!/bin/bash

# Get the directory where the script is located
PROJECT_ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Create directories for organized structure
mkdir -p "$PROJECT_ROOT/src/core" "$PROJECT_ROOT/src/protocols"
mkdir -p "$PROJECT_ROOT/include/core" "$PROJECT_ROOT/include/protocols"

# Create empty source files in respective subfolders
[ ! -f "$PROJECT_ROOT/src/core/main.cpp" ] && touch "$PROJECT_ROOT/src/core/main.cpp"
[ ! -f "$PROJECT_ROOT/src/core/User.cpp" ] && touch "$PROJECT_ROOT/src/core/User.cpp"
[ ! -f "$PROJECT_ROOT/src/core/Simulator.cpp" ] && touch "$PROJECT_ROOT/src/core/Simulator.cpp"
[ ! -f "$PROJECT_ROOT/src/protocols/WiFi4Simulator.cpp" ] && touch "$PROJECT_ROOT/src/protocols/WiFi4Simulator.cpp"

# Create empty header files in respective subfolders
[ ! -f "$PROJECT_ROOT/include/core/User.h" ] && touch "$PROJECT_ROOT/include/core/User.h"
[ ! -f "$PROJECT_ROOT/include/core/Simulator.h" ] && touch "$PROJECT_ROOT/include/core/Simulator.h"
[ ! -f "$PROJECT_ROOT/include/protocols/WiFi4Simulator.h" ] && touch "$PROJECT_ROOT/include/protocols/WiFi4Simulator.h"

# Create logs directory if it does not exist
mkdir -p "$PROJECT_ROOT/logs"
[ ! -f "$PROJECT_ROOT/logs/simulationLogs.txt" ] && touch "$PROJECT_ROOT/logs/simulationLogs.txt"

# Print the project structure
echo "Project structure created. Directory and file setup:"
echo "
$PROJECT_ROOT/
│
├── src/
│   │
│   ├── core/
│   │   ├── main.cpp        # Main application entry
│   │   ├── Simulator.cpp   # Simulator base class implementation
│   │   └── User.cpp        # User class implementation
│   │   
│   └── protocols/
│       └── WiFi4Simulator.cpp  # WiFi 4 Simulator implementation
│
└── include/
    │
    ├── core/
    │    ├──Simulator.h     # Simulator base class header
    │    └──User.h          # User class header
    │
    └── protocols/
         └── WiFi4Simulator.h  # WiFi 4 Simulator header
"
