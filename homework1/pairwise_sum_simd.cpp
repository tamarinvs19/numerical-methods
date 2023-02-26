#pragma GCC push_options
float pairwise_sum_simd(float* x, int n) {
    if (n == 1) {
        return x[0];
    }
#pragma omp simd
    int shift = (n + 1) / 2;
    for (int i = 0; i < n / 2; i++) {
        x[i] += x[i + shift];
    }
    return pairwise_sum_simd(x, shift);
}
#pragma GCC pop_options
