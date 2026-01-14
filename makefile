CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = narrative_generator
OUTPUT = narrative_output.txt

# Default target - compile the program
all: $(TARGET)

# Compile all source files
$(TARGET): main.cpp generator.cpp main.h
	$(CXX) $(CXXFLAGS) main.cpp generator.cpp -o $(TARGET)

# Run and output to console AND file
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET) $(OUTPUT)

# Quick test
test: $(TARGET)
	@echo "Running generator (first 20 lines)..."
	@./$(TARGET) | head -20