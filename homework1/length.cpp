#include <cmath>
#include "tasks.h"

float length(const float* x, int n) {
    float s = 0;
    float m = 1;

    for (int i = 0; i < n; i++) {
        if (x[i] > m) {
            float abs_value = std::fabs(x[i]);
            if (abs_value > m) {
                float scale = m / abs_value;
                s *= scale * scale;
                m = abs_value;
            }
        }
        float a = x[i] / m;
        s += a * a;
    }
    return s;
}