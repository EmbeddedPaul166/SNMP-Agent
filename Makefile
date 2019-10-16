#Generic makefile for this project

SHELL := /bin/bash

SRC_PATH := src
BUILD_PATH := build
BIN_PATH := bin

CXX := g++
CXXFLAGS += -std=c++11 -c -g

EXECUTABLE := parser
BIN := $(BIN_PATH)/$(EXECUTABLE)

SRC_EXT := cpp
SOURCES := $(shell find $(SRC_PATH) -type f -name *.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_PATH)/%, $(BUILD_PATH)/%, $(SOURCES:.$(SRC_EXT)=.o))

INC_PATH := $(shell find include/ -name '*.h' -exec dirname {} \; | sort | uniq)
INC_LIST := $(patsubst include/%, -I include/%, $(INC_PATH))
BUILD_LIST := $(patsubst include/%, $(BUILD_PATH)/%, $(INC_PATH))

INC := -I $(INC_LIST) -I /usr/local/include
LIB := -L /usr/local/lib

$(BIN): $(OBJECTS)
	@mkdir -p $(BIN_PATH)
	@echo "Linking $(BIN)..."
	$(CXX) $^ -o $(BIN) $(LIB)
	@echo "Build done"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_PATH)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $<

clean:
	@echo "Cleaning project..."
	rm -r $(BUILD_PATH)/* $(BIN_PATH)/*	
