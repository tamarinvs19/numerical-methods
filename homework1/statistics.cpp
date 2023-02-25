#include <algorithm>
#include "tasks.h"

void Statistics::update(float x) {
    if (length == 0) {
        currentMin = x;
        currentMax = x;
    } else {
        currentMin = std::min(x, currentMin);
        currentMax = std::max(x, currentMax);
    }
    currentSum += x;
    length++;

    float newMean = currentMean + (x - currentMean) / (float) length;
    sumVarM += (x - currentMean) * (x - newMean);
    currentMean = newMean;
}

int Statistics::count() const noexcept {
    return length;
}

float Statistics::min() const noexcept {
    return currentMin;
}

float Statistics::max() const noexcept {
    return currentMax;
}

float Statistics::sum() const noexcept {
    return currentSum;
}

float Statistics::mean() const noexcept {
    return currentMean;
}

float Statistics::variance() const noexcept {
    return sumVarM / (float) length;
}
