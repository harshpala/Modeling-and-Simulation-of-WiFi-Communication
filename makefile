CC=g++
CFLAGS=-std=c++17 -Iinclude
DEBUGFLAGS=-g -O0
OPTFLAGS=-O3

# Source and object files
CORE_SOURCES=$(wildcard src/core/*.cpp)
PROTOCOL_SOURCES=$(wildcard src/protocols/*.cpp)
SOURCES=$(CORE_SOURCES) $(PROTOCOL_SOURCES)
OBJECTS=$(SOURCES:src/%.cpp=build/%.o)
DEBUG_TARGET=build/WiFiSimulator_debug
RELEASE_TARGET=build/WiFiSimulator_opt

.PHONY: all clean debug optimized prepare

all: prepare debug optimized

debug: $(DEBUG_TARGET)

optimized: $(RELEASE_TARGET)

$(DEBUG_TARGET): $(OBJECTS)
	$(CC) $(DEBUGFLAGS) $(CFLAGS) $^ -o $@

$(RELEASE_TARGET): $(OBJECTS)
	$(CC) $(OPTFLAGS) $(CFLAGS) $^ -o $@

# Compile source files into object files
build/%.o: src/%.cpp
	if not exist "build" mkdir build
	if not exist "build\\core" mkdir build\\core
	if not exist "build\\protocols" mkdir build\\protocols
	$(CC) $(CFLAGS) -c $< -o $@

# Prepare the necessary directories
prepare:
	if not exist "build" mkdir build
	if not exist "build\\core" mkdir build\\core
	if not exist "build\\protocols" mkdir build\\protocols

clean:
	if exist "build" rmdir /s /q build
