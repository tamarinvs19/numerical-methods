#pragma GCC push_options
#pragma GCC optimize ("O0")
float kahan_sum(const float* x, int n) {
    float s = 0;
    float c = 0;
    for (int i = 0; i < n; i++) {
        float y = x[i] - c;
        float t = s + y;
        c = (t - s) - y;
        s = t;
    }
    return s;
}
#pragma GCC pop_options
