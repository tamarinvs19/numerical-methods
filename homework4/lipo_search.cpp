#include <iostream>
#include <vector>
#include "utils/extreme.h"
#include "utils/rastrigin.h"
#include "utils/myrandom.h"
#include "utils/constants.h"

double U(std::vector<double> fxs, std::vector<double> xs, double k, double x) {
    double min = fxs[0] + k * std::abs(xs[0] - x);
    for (size_t i = 1; i < xs.size(); i++) {
        double u = fxs[i] + k * std::abs(xs[i] - x);
        if (min < u) {
            min = u;
        }
    }
    return min;
}

template<typename Function>
Extreme lipo_search(Function f, double x) {
    int steps = 0;
    Extreme extreme = {x, f(x), 0};
    std::vector<double> xs = {x};
    std::vector<double> fxs = {f(x)};
//    std::vector<double> ls = {0};
    double l = 7;

    while (steps < STEPS) {
//        std::vector<double> lis;
//        for (size_t i = 0; i < xs.size(); i++) {
//            double max_i = 0;
//            for (size_t j = 0; j < xs.size(); j++) {
//                if (i != j) {
//                    max_i = std::max(max_i, std::abs(fxs[i] - fxs[j]) / std::abs(xs[i] - xs[j]));
//                }
//            }
//            if (ls[i] >= max_i) {
//                lis.push_back(ls[i]);
//            }
//        }
//        double l_ip1 =
        double max_u = 0;
        double best_x = 0;
        double best_value = 0;
        for (int i = 0; i < 50; i++) {
            double dx = myrandom();  // [-1, 1];
            double next_x = dx + x;
            double next_value = f(next_x);
            double next_u = U(fxs, xs, l, x);
            if (max_u < next_u) {
                max_u = next_u;
                best_x = next_x;
                best_value = next_value;
            }
        }
        steps++;

        double diff = best_value - extreme.value;
        if (std::abs(diff) < EPS_F_DIFF) {
            break;
        }
        if (diff < 0) {
            extreme.x = best_x;
            extreme.value = best_value;
        }
        xs.push_back(best_x);
        fxs.push_back(best_value);
    }
    extreme.step = steps;
    return extreme;
}

void lipo_test() {
    int steps_count = 0;
    for (int i = 0; i < TEST_COUNT; i++) {
        double init = myrandom() * X_NORM;
        Extreme extreme = lipo_search(rastrigin, init);
        steps_count += extreme.step;
    }
    std::cout << "LiPO search:\taverage " << (float)steps_count / TEST_COUNT << " steps" << std::endl;
}
