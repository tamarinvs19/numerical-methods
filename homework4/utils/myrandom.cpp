#include <random>
#include "myrandom.h"

double myrandom() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    return dist(mt);
}

int choose(int count) {
    double random_value = (myrandom() + 1) / 2 * count;
    return std::min((int)random_value, count-1);
}

std::pair<int, int> choose_pair(int count) {
    int first = choose(count);
    int second = choose(count);
    while (second == first) {
        second = choose(count);
    }
    return {first, second};
}
