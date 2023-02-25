#pragma GCC push_options
float pairwise_sum_simd(float* x, int n) {
    while (n > 1) {
#pragma omp simd
        for (int i = 0; i < n / 2; i++) {
            x[i] = x[2 * i] + x[2 * i + 1];
        }
        if (n % 2 == 1) {
            x[n / 2] = x[n - 1];
        }
        n = (n + 1) / 2;
    }
    return x[0];
}
#pragma GCC pop_options
