# Makefile for C++ Matrix Operations Lab
# EECS 348 Lab 9

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = matrix
SOURCE = matrix.cpp

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean up object files and executable
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run