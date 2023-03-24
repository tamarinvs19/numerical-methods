#ifndef HOMEWORK3_RASTRIGIN_H
#define HOMEWORK3_RASTRIGIN_H

#include <cmath>

double rastrigin(double x) {
    return 10.0 + x * x - 10 * std::cos(2 * M_PI * x);
}

#endif //HOMEWORK3_RASTRIGIN_H
