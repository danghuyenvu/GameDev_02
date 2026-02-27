# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Libraries
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Source files
SRC = src/main.cpp src/Arena.cpp src/Ball.cpp

# Output
TARGET = game

all:
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LIBS)

run: all
	./$(TARGET).exe

clean:
	rm -f $(TARGET).exe