#include <cmath>

float polynomial(float x, const float* a, int n) {
    float result = a[n-1];
    for (int i = n-2; i >= 0; i--) {
        result = std::fma(x, result, a[i]);
    }
    return result;
}
