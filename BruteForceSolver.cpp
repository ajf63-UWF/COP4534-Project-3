#include "BruteForceSolver.hpp"
#include "Permutation.hpp"
#include "Timer.hpp"

#include <vector>
#include <iostream>

BruteForceResult::BruteForceResult() : elapsedSeconds(0.0) {}

BruteForceSolver::BruteForceSolver(const Graph& graph) : graph(graph) {}

BruteForceResult BruteForceSolver::solve(int numberOfCities) const {
    BruteForceResult result;

    if (numberOfCities < 2 || numberOfCities > graph.getMaxCities()) {
        return result; // Return empty result if the number of cities is invalid
    }

    Timer timer;
    timer.start();

    std::vector<int> permutation;
    initializePermutation(permutation, 1, numberOfCities - 1);

    Tour currentTour;
    currentTour.cities.push_back(0); // Start from the first city

    for (int city : permutation) {
        currentTour.cities.push_back(city);
    }

    currentTour.cost = calculateTourCost(graph, currentTour.cities);

    result.bestTour = currentTour;

    while (perm1(permutation)) {
        if (timer.getElapsedSeconds() > 300.0) {
            std::cout << "Brute force exceeded 5 minutes. Stopping search early." << std::endl;
            break;
        }

        currentTour.cities.clear();
        currentTour.cities.push_back(0); // Start from the first city

        for (int city : permutation) {
            currentTour.cities.push_back(city);
        }

        currentTour.cost = calculateTourCost(graph, currentTour.cities);

        if (currentTour.cost < result.bestTour.cost) {
            result.bestTour = currentTour;
        }
    }

    timer.stop();
    result.elapsedSeconds = timer.getElapsedSeconds();

    return result;
}