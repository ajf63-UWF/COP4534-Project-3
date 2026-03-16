#ifndef TOUR_HPP
#define TOUR_HPP

#include "Graph.hpp"
#include <vector>

struct Tour {
    std::vector<int> cities;
    double cost;

    Tour();
};

double calculateTourCost(const Graph& graph, const std::vector<int>& cities);
void printTour(const Tour& tour);

#endif // TOUR_HPP