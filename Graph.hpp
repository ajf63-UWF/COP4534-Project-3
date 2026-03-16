#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>

class Graph {
private:
    static const int MAX_CITIES = 20;
    double adjacencyMatrix[MAX_CITIES][MAX_CITIES];
    
public:
    Graph();

    bool loadFromFile(const std::string& filename);

    double getDistance(int from, int to) const;

    int getMaxCities() const;

    void printMatrix() const;
};

#endif // GRAPH_HPP