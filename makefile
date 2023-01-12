TARGET = tetris

CXX := g++
CXXFLAGS := -std=c++14 -lncurses -pthread

SOURCES = $(wildcard ./src/*.cpp)
INCLUDES = ./include

$(TARGET):
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) $(SOURCES) main.cpp -o $(TARGET)
