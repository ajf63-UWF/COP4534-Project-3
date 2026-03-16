#include "Graph.hpp"

#include <fstream>
#include <iostream>
#include <iomanip>

Graph::Graph() {
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0.0; // Distance to itself is zero
            } else {
                adjacencyMatrix[i][j] = 0.0; // Initialize with zero
            }
        }
    }
}

bool Graph::loadFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0.0; // Distance to itself is zero
            } else {
                if (!(inputFile >> adjacencyMatrix[i][j])) {
                    std::cerr << "Error: File does not contain enough distance values." << filename << std::endl;
                    return false;
                }
            }
        }
    }

    double extraValue;
    if (inputFile >> extraValue) {
        std::cerr << "Warning: File contains extra data beyond the expected 380 values." << std::endl;
    }

    return true;
}

double Graph::getDistance(int from, int to) const {
    if (from < 0 || from >= MAX_CITIES || to < 0 || to >= MAX_CITIES) {
        std::cerr << "Error: City index out of bounds." << std::endl;
        return -1.0; // Return -1 to indicate an error
    }

    return adjacencyMatrix[from][to];
}

int Graph::getMaxCities() const {
    return MAX_CITIES;
}

void Graph::printMatrix() const {
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            std::cout << std::setw(10) << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}