#include "GeneticSolver.hpp"
#include "Timer.hpp"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>

GeneticResult::GeneticResult() : elapsedSeconds(0.0) {}

GeneticSolver::GeneticSolver(const Graph& graph) : graph(graph) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Tour GeneticSolver::createRandomTour(int numberOfCities) const {
    Tour tour;

    // Keep city 0 fixed as the starting city
    tour.cities.push_back(0);

    for (int i = 1; i < numberOfCities; i++) {
        tour.cities.push_back(i);
    }

    // Shuffle cities 1 through numberOfCities - 1
    for (int i = 1; i < numberOfCities; i++) {
        int randomIndex = 1 + (std::rand() % (numberOfCities - 1));
        std::swap(tour.cities[i], tour.cities[randomIndex]);
    }

    tour.cost = calculateTourCost(graph, tour.cities);
    return tour;
}

Tour GeneticSolver::mutateTour(const Tour& originalTour, int numberOfCities) const {
    Tour mutatedTour = originalTour;

    if (numberOfCities <= 2) {
        return mutatedTour;
    }

    // Swap two random cities, excluding city 0
    int index1 = 1 + (std::rand() % (numberOfCities - 1));
    int index2 = 1 + (std::rand() % (numberOfCities - 1));

    while (index2 == index1) {
        index2 = 1 + (std::rand() % (numberOfCities - 1));
    }

    std::swap(mutatedTour.cities[index1], mutatedTour.cities[index2]);
    mutatedTour.cost = calculateTourCost(graph, mutatedTour.cities);

    return mutatedTour;
}

void GeneticSolver::evaluatePopulation(std::vector<Tour>& population) const {
    for (size_t i = 0; i < population.size(); i++) {
        population[i].cost = calculateTourCost(graph, population[i].cities);
    }
}

Tour GeneticSolver::getBestTour(const std::vector<Tour>& population) const
{
    Tour bestTour = population[0];

    for (size_t i = 1; i < population.size(); i++) {
        if (population[i].cost < bestTour.cost) {
            bestTour = population[i];
        }
    }

    return bestTour;
}

GeneticResult GeneticSolver::solve(int numberOfCities,
                                   int populationSize,
                                   int numberOfGenerations,
                                   double mutationPercent) const {
    GeneticResult result;

    if (numberOfCities < 2 || numberOfCities > graph.getMaxCities()) {
        return result;
    }

    if (populationSize <= 0 || numberOfGenerations <= 0) {
        return result;
    }

    if (mutationPercent < 0.0 || mutationPercent > 100.0) {
        return result;
    }

    Timer timer;
    timer.start();

    std::vector<Tour> population;

    // Create initial population
    for (int i = 0; i < populationSize; i++) {
        population.push_back(createRandomTour(numberOfCities));
    }

    evaluatePopulation(population);
    result.bestTour = getBestTour(population);

    for (int generation = 0; generation < numberOfGenerations; generation++) {
        std::sort(population.begin(), population.end(),
            [](const Tour& a, const Tour& b) {
                return a.cost < b.cost;
            });

        std::vector<Tour> nextPopulation;

        // Keep exactly one elite
        nextPopulation.push_back(population[0]);

        int mutationCount = static_cast<int>((mutationPercent / 100.0) * populationSize);

        // Make sure we do not overfill the next generation
        if (mutationCount > populationSize - 1) {
            mutationCount = populationSize - 1;
        }

        // Create mutations from strong tours
        for (int i = 0; i < mutationCount; i++) {
            int parentIndex = i % population.size();
            Tour mutated = mutateTour(population[parentIndex], numberOfCities);
            nextPopulation.push_back(mutated);
        }

        // Fill the rest with random tours
        while (static_cast<int>(nextPopulation.size()) < populationSize) {
            nextPopulation.push_back(createRandomTour(numberOfCities));
        }

        population = nextPopulation;
        evaluatePopulation(population);

        Tour generationBest = getBestTour(population);
        if (generationBest.cost < result.bestTour.cost) {
            result.bestTour = generationBest;
        }
    }

    timer.stop();
    result.elapsedSeconds = timer.getElapsedSeconds();

    return result;
}