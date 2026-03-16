CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = tsp

OBJS = main.o Graph.o Tour.o Timer.o Permutation.o BruteForceSolver.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Graph.hpp BruteForceSolver.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Graph.o: Graph.cpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c Graph.cpp

Tour.o: Tour.cpp Tour.hpp Graph.hpp
	$(CXX) $(CXXFLAGS) -c Tour.cpp

Timer.o: Timer.cpp Timer.hpp
	$(CXX) $(CXXFLAGS) -c Timer.cpp

Permutation.o: Permutation.cpp Permutation.hpp
	$(CXX) $(CXXFLAGS) -c Permutation.cpp

BruteForceSolver.o: BruteForceSolver.cpp BruteForceSolver.hpp Graph.hpp Tour.hpp Permutation.hpp Timer.hpp
	$(CXX) $(CXXFLAGS) -c BruteForceSolver.cpp

clean:
	rm -f $(OBJS) $(TARGET)