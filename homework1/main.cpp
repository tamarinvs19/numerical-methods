#include "tests/polynomial_test.cpp"
#include "tests/kahan_sum_test.cpp"
#include "tests/pairwise_sum_simd_test.cpp"
#include "tests/statistics_test.cpp"
#include "tests/length_test.cpp"

int main() {
    test_polynomial();
    test_kahan_sum();
    test_pairwise();
    test_statistics();
    test_length();
    return 0;
}
