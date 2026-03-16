#include <iostream>
#include <iomanip>

#include "Graph.hpp"
#include "BruteForceSolver.hpp"
#include "GeneticSolver.hpp"

int main()
{
    Graph graph;

    if (!graph.loadFromFile("distances.txt")) {
        std::cerr << "Failed to load distances.txt" << std::endl;
        return 1;
    }

    int numberOfCities;
    int populationSize;
    int numberOfGenerations;
    double mutationPercent;

    std::cout << "Enter number of cities to run: ";
    std::cin >> numberOfCities;

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

    if (numberOfCities < 2 || numberOfCities > graph.getMaxCities()) {
        std::cerr << "Number of cities must be between 2 and "
                  << graph.getMaxCities() << "." << std::endl;
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
    BruteForceResult bruteForceResult = bruteForceSolver.solve(numberOfCities);

    GeneticSolver geneticSolver(graph);
    GeneticResult geneticResult = geneticSolver.solve(
        numberOfCities, populationSize, numberOfGenerations, mutationPercent);


    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n===== Results =====\n";
    std::cout << "Number of cities: " << numberOfCities << std::endl;
    std::cout << "Optimal cost from brute force: "
              << bruteForceResult.bestTour.cost << std::endl;
    std::cout << "Time brute force took: "
              << bruteForceResult.elapsedSeconds << " seconds" << std::endl;
    std::cout << "Cost from GA: "
              << geneticResult.bestTour.cost << std::endl;
    std::cout << "Time GA took: "
              << geneticResult.elapsedSeconds << " seconds" << std::endl;
    std::cout << "Percent of optimal: "
              << (geneticResult.bestTour.cost / bruteForceResult.bestTour.cost) * 100.0
              << "%" << std::endl;

    std::cout << "\nParameters used:" << std::endl;
    std::cout << "Population size: " << populationSize << std::endl;
    std::cout << "Generations: " << numberOfGenerations << std::endl;
    std::cout << "Mutation percentage: " << mutationPercent << "%" << std::endl;
    return 0;
}