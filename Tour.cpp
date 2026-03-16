#include "Tour.hpp"

#include <iostream>
#include <iomanip>
#include <limits>

Tour::Tour() : cost(0.0) {}
Tour::Tour() : cost(std::numeric_limits<double>::max()) {}

double calculateTourCost(const Graph& graph, const std::vector<int>& cities) {
    if (cities.empty()) {
        return 0.0; // No cities, no cost
    }

    double totalCost = 0.0;

    for (size_t i = 0; i < cities.size() - 1; i++) {
        totalCost += graph.getDistance(cities[i], cities[i + 1]);
    }

    totalCost += graph.getDistance(cities.back(), cities.front());

    return totalCost;
}

void printTour(const Tour& tour) {
    std::cout << "Tour: ";

    for (size_t i = 0; i < tour.cities.size(); i++) {
        std::cout << tour.cities[i];
        if (i < tour.cities.size() - 1) {
            std::cout << " -> ";
        }
    }

    if (!tour.cities.empty()) {
        std::cout << " -> " << tour.cities.front(); // Return to the starting city
    }

    std::cout << "\nCost: " << std::fixed << std::setprecision(2) << tour.cost << std::endl;
}