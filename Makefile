GXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = tsp
OBJS = main.o Permutation.o Timer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(GXX) $(CXXFLAGS) -o $(TARGET) $(OBJS
	
main.o: main.cpp Permutation.hpp Timer.hpp
	$(GXX) $(CXXFLAGS) -c main.cpp

Permutation.o: Permutation.cpp Permutation.hpp
	$(GXX) $(CXXFLAGS) -c Permutation.cpp

Timer.o: Timer.cpp Timer.hpp
	$(GXX) $(CXXFLAGS) -c Timer.cpp

clean:
	rm -f $(TARGET) $(OBJS)