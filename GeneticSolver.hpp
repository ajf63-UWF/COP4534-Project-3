#ifndef GENETICSOLVER_HPP
#define GENETICSOLVER_HPP

#include "Graph.hpp"
#include "Tour.hpp"

#include <vector>

struct GeneticResult {
    Tour bestTour;
    double elapsedSeconds;

    GeneticResult();
};

class GeneticSolver {
private:
    const Graph& graph;

    Tour createRandomTour(int numberOfCities) const;
    Tour mutateTour(const Tour& originalTour, int numberOfCities) const;
    void evaluatePopulation(std::vector<Tour>& population) const;
    Tour getBestTour(const std::vector<Tour>& population) const;

public:
    GeneticSolver(const Graph& graph);

    GeneticResult solve(int numberOfCities,
                        int populationSize,
                        int numberOfGenerations,
                        double mutationPercent) const;
};

#endif