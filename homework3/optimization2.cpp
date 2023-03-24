#include <cstdlib>
#include <cassert>
#include <iostream>
#include "utils/rastrigin.h"
#include "utils/constants.h"

struct Point2d {
    double x, y;
};

float diffPoint(Point2d a, Point2d b) {
    return std::fabs(a.x - b.x) + std::fabs(b.x - b.y);
}

struct Extreme2d {
    Point2d p;
    int steps;
};

template<typename Function>
Extreme2d bisect2d(Function f, Function fd, Point2d a, Point2d b, int step) {
    Point2d mid = Point2d{(a.x + b.x) / 2, (a.y + b.y) / 2};
    if (step > MAX_STEPS) return {mid, step};

    if (std::fabs(f(mid.x) + f(mid.y)) < 2*EPS_F_DIFF || diffPoint(a, b) <= 2*EPS_X_DIFF) {
        return {mid, step};
    }
    if (std::fabs(a.x - b.x) > EPS_X_DIFF && fd(a.x) * fd(b.x) < 0.0) {
        if (fd(a.x) * fd(mid.x) < 0.0) {
            return bisect2d(f, fd, a, Point2d{mid.x, b.y}, step + 1);
        }
        return bisect2d(f, fd, Point2d{mid.x, a.y}, b, step + 1);
    }
    if (fd(a.y) * fd(mid.y) < 0.0) {
        return bisect2d(f, fd, a, Point2d{b.x, mid.y}, step + 1);
    }
    return bisect2d(f, fd, Point2d{a.x, mid.y}, b, step + 1);
}

template<typename Function>
Extreme2d newton2d(Function fd, Function fdd, Point2d p, int step) {
    if (step > MAX_STEPS) return {p, step};
    if (std::abs(fdd(p.x)) < EPS_F_DIFF && std::abs(fdd(p.y)) < EPS_F_DIFF) return {p, step};

    double next_x;
    double next_y;
    if (std::abs(fdd(p.x)) < EPS_F_DIFF)
        next_x = p.x;
    else
        next_x = p.x - fd(p.x) / fdd(p.x);

    if (std::abs(fdd(p.y)) < EPS_F_DIFF)
        next_y = p.y;
    else
        next_y = p.y - fd(p.y) / fdd(p.y);

    if (std::abs(next_x - p.x) < EPS_X_DIFF && std::abs(next_y - p.y) < EPS_X_DIFF)
        return {p, step};

    return newton2d(fd, fdd, {next_x, next_y}, step + 1);
}

std::pair<Point2d, Point2d> generate_sector_2d() {
    float a = -std::rand() / ((float)(RAND_MAX / MAX_X));
    float b = -std::rand() / ((float)(RAND_MAX / MAX_X));
    float c = std::rand() / ((float)(RAND_MAX / MAX_X));
    float d = std::rand() / ((float)(RAND_MAX / MAX_X));
    return {{std::min(a, b), std::max(a, b)}, {std::min(c, d), std::max(c, d)}};
}

void bisect_test_2(int n) {
    int good_executions = 0;
    int steps = 0;
    for (int i = 0; i < n; i++) {
        auto [a, b] = generate_sector_2d();
        auto extreme = bisect2d(rastrigin, rastriginD, a, b, 0);
        if (extreme.steps <= MAX_STEPS) {
            good_executions++;
            steps += extreme.steps;
        }
    }
    std::cout << "Bisect: " << (float) steps / good_executions << " steps per one execution. " << (float) good_executions / n * 100 << "% success executions." << std::endl;
}

void newton_test_2(int n) {
    int good_executions = 0;
    int steps = 0;
    for (int i = 0; i < n; i++) {
        auto x = std::rand() / ((float) RAND_MAX / MAX_X);
        auto y = std::rand() / ((float) RAND_MAX / MAX_X);

        auto extreme = newton2d(rastriginD, rastriginDD, {x, y}, 0);
        if (extreme.steps <= MAX_STEPS) {
            good_executions++;
            steps += extreme.steps;
        }
    }
    std::cout << "Newton: " << (float) steps / good_executions << " steps per one execution. " << (float) good_executions / n * 100 << "% success executions." << std::endl;
}

void test2d() {
    bisect_test_2(1000);
    newton_test_2(1000);
}
