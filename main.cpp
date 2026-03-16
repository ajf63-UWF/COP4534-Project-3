#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Graph.hpp"
#include "BruteForceSolver.hpp"
#include "GeneticSolver.hpp"

struct ExperimentResult {
    int numberOfCities;
    double bruteForceCost;
    double bruteForceTime;
    double gaCost;
    double gaTime;
    double percentOfOptimal;
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Graph graph;

    if (!graph.loadFromFile("distances.txt")) {
        std::cerr << "Failed to load distances.txt" << std::endl;
        return 1;
    }

    int populationSize;
    int numberOfGenerations;
    double mutationPercent;

    std::cout << "Enter number of tours in each generation: ";
    std::cin >> populationSize;

    std::cout << "Enter number of generations to run: ";
    std::cin >> numberOfGenerations;

    std::cout << "Enter mutation percentage of a generation: ";
    std::cin >> mutationPercent;

    if (std::cin.fail()) {
        std::cerr << "Invalid input." << std::endl;
        return 1;
    }

    if (populationSize <= 0 || numberOfGenerations <= 0) {
        std::cerr << "Population size and number of generations must be positive."
                  << std::endl;
        return 1;
    }

    if (mutationPercent < 0.0 || mutationPercent > 100.0) {
        std::cerr << "Mutation percentage must be between 0 and 100."
                  << std::endl;
        return 1;
    }

    BruteForceSolver bruteForceSolver(graph);
    GeneticSolver geneticSolver(graph);

    std::vector<ExperimentResult> results;

    for (int numberOfCities = 10; numberOfCities <= graph.getMaxCities(); numberOfCities++) {
        std::cout << "\nRunning experiment for " << numberOfCities << " cities..." << std::endl;

        BruteForceResult bruteForceResult = bruteForceSolver.solve(numberOfCities);
        GeneticResult geneticResult = geneticSolver.solve(
            numberOfCities,
            populationSize,
            numberOfGenerations,
            mutationPercent
        );

        ExperimentResult experiment;
        experiment.numberOfCities = numberOfCities;
        experiment.bruteForceCost = bruteForceResult.bestTour.cost;
        experiment.bruteForceTime = bruteForceResult.elapsedSeconds;
        experiment.gaCost = geneticResult.bestTour.cost;
        experiment.gaTime = geneticResult.elapsedSeconds;
        experiment.percentOfOptimal =
            (geneticResult.bestTour.cost / bruteForceResult.bestTour.cost) * 100.0;

        results.push_back(experiment);

        if (bruteForceResult.elapsedSeconds > 300.0) {
            std::cout << "Brute force exceeded 5 minutes at "
                      << numberOfCities << " cities. Stopping experiments."
                      << std::endl;
            break;
        }
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n===== Experiment Results =====\n";
    std::cout << std::left
              << std::setw(8)  << "Cities"
              << std::setw(18) << "Brute Cost"
              << std::setw(18) << "Brute Time(s)"
              << std::setw(18) << "GA Cost"
              << std::setw(18) << "GA Time(s)"
              << std::setw(18) << "% Optimal"
              << std::endl;

    for (size_t i = 0; i < results.size(); i++) {
        std::cout << std::left
                  << std::setw(8)  << results[i].numberOfCities
                  << std::setw(18) << results[i].bruteForceCost
                  << std::setw(18) << results[i].bruteForceTime
                  << std::setw(18) << results[i].gaCost
                  << std::setw(18) << results[i].gaTime
                  << std::setw(18) << results[i].percentOfOptimal
                  << std::endl;
    }

    std::cout << "\nParameters used:" << std::endl;
    std::cout << "Population size: " << populationSize << std::endl;
    std::cout << "Generations: " << numberOfGenerations << std::endl;
    std::cout << "Mutation percentage: " << mutationPercent << "%" << std::endl;

    return 0;
}