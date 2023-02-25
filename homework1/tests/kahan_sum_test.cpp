#include <vector>
#include <iomanip>
#include <iostream>
#include "../tasks.h"

float simple_sum(const float* x, int n) {
    float s = 0;
    for (int i = 0; i < n; i++) {
        s += x[i];
    }
    return s;
}

void test_kahan_sum() {
    std::cout << "Kahan test stated" << std::endl;
    int n = 9000000;
    float elem = 1.0 / 9.0;
    std::vector<float> x(n, elem);
    float real_sum = 1000000;

    float kahan_sum_answer = kahan_sum(x.data(), x.size());
    float simple_sum_answer = simple_sum(x.data(), x.size());

    float diff_kahan = kahan_sum_answer - real_sum;
    float diff_simple = simple_sum_answer - real_sum;

    std::cout << std::setprecision(60) << "Kahan result: " << kahan_sum_answer << " (delta = " << diff_kahan << ")" << std::endl;
    std::cout << std::setprecision(60) << "Simple result: " << simple_sum_answer << " (delta = " << diff_simple << ")" << std::endl;

    std::cout << "Kahan test completed" << std::endl;

    std::ios_base::fmtflags f( std::cout.flags() );
    std::cout.flags(f);
}
