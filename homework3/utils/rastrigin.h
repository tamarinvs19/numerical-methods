#ifndef HOMEWORK3_RASTRIGIN_H
#define HOMEWORK3_RASTRIGIN_H

#include <cmath>

double rastrigin(double x) {
    return 10.0 + x * x - 10 * std::cos(2 * M_PI * x);
}

double rastriginD(double x) {
    return 2.0 * x + 20 * M_PI * std::sin(2 * M_PI * x);
}

double rastriginDD(double x) {
    return 2.0 + 40.0 * M_PI * M_PI * std::cos(2 * M_PI * x);
}

#endif //HOMEWORK3_RASTRIGIN_H
