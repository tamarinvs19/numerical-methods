#include <cstdlib>
#include <cassert>
#include <iostream>
#include "utils/rastrigin.h"
#include "utils/constants.h"

struct Extreme {
    double x;
    int steps;
};

template<typename Function>
Extreme bisect1d(Function f, Function fd, double a, double b, int step) {
    double mid = a + (b - a) / 2;
    if (step > MAX_STEPS) return {mid, step};

    if (std::fabs(f(mid)) < EPS_F_DIFF) {
        return {mid, step};
    }
    if (fd(a) * fd(mid) < 0.0) {
        return bisect1d(f, fd, a, mid, step + 1);
    }
    return bisect1d(f, fd, mid, b, step + 1);
}

template<typename Function>
Extreme newton1d(Function fd, Function fdd, double x, int step) {
    if (step > MAX_STEPS) return {x, step};
    double fd_value = fd(x);
    double fdd_value = fdd(x);

    if (std::fabs(fd_value) < EPS_F_DIFF || std::fabs(fdd_value) < EPS_F_DIFF) return {x, step};

    double next = x - fd_value / fdd_value;
    if (std::fabs(next - x) < EPS_X_DIFF) return {x, step};

    return newton1d(fd, fdd, next, step + 1);
}

std::pair<float, float> generate_sector() {
    float a = -std::rand() / ((float)(RAND_MAX / MAX_X));
    float b = std::rand() / ((float)(RAND_MAX / MAX_X));
    return {std::min(a, b), std::max(a, b)};
}

void bisect_test(int n) {
    int good_executions = 0;
    int steps = 0;
    for (int i = 0; i < n; i++) {
        auto [a, b] = generate_sector();
        auto extreme = bisect1d(rastrigin, rastriginD, a, b, 0);
        if (extreme.steps <= MAX_STEPS) {
            good_executions++;
            steps += extreme.steps;
        }
    }
    std::cout << "Bisect: " << (float) steps / good_executions << " steps per one execution. " << (float) good_executions / n * 100 << "% success executions." << std::endl;
}

void newton_test(int n) {
    int good_executions = 0;
    int steps = 0;
    for (int i = 0; i < n; i++) {
        auto x = std::rand() / ((float) RAND_MAX / MAX_X);

        auto extreme = newton1d(rastriginD, rastriginDD, x, 0);
        if (extreme.steps <= MAX_STEPS) {
            good_executions++;
            steps += extreme.steps;
        }
    }
    std::cout << "Newton: " << (float) steps / good_executions << " steps per one execution. " << (float) good_executions / n * 100 << "% success executions." << std::endl;
}

void test1d() {
    bisect_test(1000);
    newton_test(1000);
}
