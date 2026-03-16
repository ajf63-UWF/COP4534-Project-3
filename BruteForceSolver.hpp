#ifndef BRUTEFORCESOLVER_HPP
#define BRUTEFORCESOLVER_HPP

#include "Graph.hpp"
#include "Tour.hpp"

struct BruteForceResult {
    Tour bestTour;
    double elapsedSeconds;

    BruteForceResult();
};

class BruteForceSolver {
private:
    const Graph& graph;

public:
    BruteForceSolver(const Graph& graph);

    BruteForceResult solve(int numberOfCities) const;
};

#endif // BRUTEFORCESOLVER_HPP