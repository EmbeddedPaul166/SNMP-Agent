#Generic makefile for this project

SHELL := /bin/bash

SRC_PATH := src
INC_PATH := include
BUILD_PATH := build
BIN_PATH := bin

CXX := g++

CXXFLAGS += -g -std=c++17 -Wall -Wextra -pedantic

EXECUTABLE := snmp_agent
BIN := $(BIN_PATH)/$(EXECUTABLE)

SRC_CPP_EXT := cpp
SOURCES := $(shell find $(SRC_PATH) -type f -name *.$(SRC_CPP_EXT))
OBJECTS := $(patsubst $(SRC_PATH)/%, $(BUILD_PATH)/%, $(SOURCES:.$(SRC_CPP_EXT)=.o))

INC := -I $(INC_PATH)

$(BIN): $(OBJECTS) 
	@mkdir -p $(BIN_PATH)	
	@echo "Linking $(BIN)..."
	$(CXX) $^ $(CXXFLAGS) -o $(BIN).elf	
	@echo "Linking done"
	@echo "Build done"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_CPP_EXT) 
	@mkdir -p $(BUILD_PATH)
	@echo "Compiling $<..."
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@
	@echo ""

.PHONY: clean

clean:
	@echo "Cleaning project..."
	rm -r $(BUILD_PATH)/* $(BIN_PATH)/*	
