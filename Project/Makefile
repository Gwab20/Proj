# MinGW Makefile for Windows
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -mwindows
LDFLAGS = -Llibs -lwinmm
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = game.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(EXEC) src\*.o