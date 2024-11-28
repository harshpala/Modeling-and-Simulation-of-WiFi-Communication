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

# Library targets
STATIC_LIB=build/libWiFiSimulator.a
SHARED_LIB=build/libWiFiSimulator.so

.PHONY: all clean debug optimized prepare static shared

all: prepare debug optimized static shared

debug: $(DEBUG_TARGET)

optimized: $(RELEASE_TARGET)

# Debug and optimized targets
$(DEBUG_TARGET): $(OBJECTS)
	$(CC) $(DEBUGFLAGS) $(CFLAGS) $^ -o $@

$(RELEASE_TARGET): $(OBJECTS)
	$(CC) $(OPTFLAGS) $(CFLAGS) $^ -o $@

# Compile source files into object files
build/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Static library creation
static: $(STATIC_LIB)

$(STATIC_LIB): $(OBJECTS)
	ar rcs $@ $^

# Shared library creation
shared: $(SHARED_LIB)

$(SHARED_LIB): $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

# Prepare the necessary directories (only once)
prepare:
	if not exist "build" mkdir build
	if not exist "build\\core" mkdir build\\core
	if not exist "build\\protocols" mkdir build\\protocols

clean:
	if exist "build" rmdir /s /q build
