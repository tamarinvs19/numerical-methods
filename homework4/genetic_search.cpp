#include <iostream>
#include <vector>
#include <algorithm>
#include "utils/extreme.h"
#include "utils/rastrigin.h"
#include "utils/myrandom.h"
#include "utils/constants.h"

unsigned int number_to_gray(unsigned int n) {
    return n ^ (n >> 1);
}

unsigned int gray_to_number(unsigned int g) {
    unsigned int n = 0;
    for (; g!=0; g >>= 1) { n ^= g; }
    return n;
}

template<typename Function>
Extreme genetic_search(Function f, double x) {
    int steps = 0;
    Extreme extreme;

    int population_size = 20;
    int best_population_size = 5;
    int pair_count = 8;
    int mutations_count = 3;

    std::vector<unsigned int> population;
    std::vector<unsigned int> gray_population;
    std::vector<double> values;
    std::vector<int> best_population;
    std::vector<unsigned int> gray_children;
    std::vector<double> children;

    while (steps < STEPS) {
        // create population
        while (population.size() < population_size) {
            population.push_back((unsigned int)((1 << 30) * (myrandom() + 1)));
        }

        for (int i = 0; i < population_size; i++) {
            gray_population.push_back(number_to_gray(population[i]));
        }

        // selection
        for (int i = 0; i < population_size; i++) {
            values.push_back(f(population[i]));
        }
        std::nth_element(values.begin(), values.begin() + best_population_size, values.end(), std::less());
        double nth_value = values[best_population_size];

        for (int i = 0; i < population_size; i++) {
            if ((best_population.size() < best_population_size) && (f(population[i]) >= nth_value)) {
                best_population.push_back(i);
            }
        }

        // breeding
        for (int i = 0; i < pair_count; i++) {
            auto parents = choose_pair(best_population.size());
            int index = choose(32);
            unsigned int part1 = ((1 << 31) + ((1 << 31) - (unsigned int)1)) ^ ((1 << index) - 1);
            unsigned int part2 = !part1;
            gray_children.push_back(gray_population[parents.first] & part1 + gray_population[parents.second] & part2);
            gray_children.push_back(gray_population[parents.first] & part2 + gray_population[parents.second] & part1);
        }

        // mutation
        for (int i = 0; i < gray_children.size(); i++) {
            int local_mutations_count = choose(mutations_count);
            for (int j = 0; j < local_mutations_count; j++) {
                int index = choose(32);
                gray_children[i] ^= (1 << index);
            }
        }

        // new generation
        for (auto child : gray_children) {
            double child_n = gray_to_number(child);
            double f_value = f(child_n);
            steps++;
            if (std::abs(f_value - extreme.value) < EPS_F_DIFF) {
                break;
            }
            if (extreme.step == 0 || f_value < extreme.value) {
                extreme = {child_n, f_value, steps};
            }
            children.push_back(child_n);
        }

        // clear
        population.clear();
        gray_population.clear();
        best_population.clear();
        values.clear();
        gray_children.clear();

        for (auto child : children) {
            population.push_back((unsigned int)child);
        }
        children.clear();
    }
    return extreme;
}

void genetic_test() {
    int steps_count = 0;
    for (int i = 0; i < TEST_COUNT; i++) {
        double init = myrandom() * X_NORM;
        Extreme extreme = genetic_search(rastrigin, init);
        steps_count += extreme.step;
    }
    std::cout << "Genetic search:\taverage " << (float)steps_count / TEST_COUNT << " steps" << std::endl;
}
