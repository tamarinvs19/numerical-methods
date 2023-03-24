#include <iostream>
#include "utils/extreme.h"
#include "utils/rastrigin.h"
#include "utils/myrandom.h"
#include "utils/constants.h"

template<typename Function>
Extreme random_search(Function f, double x) {
    int steps = 0;
    Extreme extreme = {x, f(x), 0};
    while (steps < STEPS) {
        double dx = myrandom();  // [-1, 1];
        double next_x = x + dx;
        double next_value = f(next_x);
        steps++;

        double diff = next_value - extreme.value;
        if (std::abs(diff) < EPS_F_DIFF) {
            break;
        }
        if (diff < 0) {
            extreme.x = next_x;
            extreme.value = next_value;
            x = next_x;
        }
    }
    extreme.step = steps;
    return extreme;
}

void random_test() {
    int steps_count = 0;
    for (int i = 0; i < TEST_COUNT; i++) {
        double init = myrandom() * X_NORM;
        Extreme extreme = random_search(rastrigin, init);
        steps_count += extreme.step;
    }
    std::cout << "Random search:\taverage " << (float)steps_count / TEST_COUNT << " steps" << std::endl;
}