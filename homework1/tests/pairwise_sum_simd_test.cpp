#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>
#include "../tasks.h"

float simple_array_sum(const float* x, int n) {
    float acc = 0;
    for (int i = 0; i < n; i++) {
        acc += x[i];
    }
    return acc;
}

void test_pairwise_sum_simd() {
    std::vector<float> vec(1002, 10000.f + 1.f/3);
    float expected_sum = 10020334.f;
    float pairwise_sum = pairwise_sum_simd(vec.data(), vec.size());
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple test completed" << std::endl;
}

void test_compare_with_simple() {
    int n = 1001;
    std::vector<float> vec(n, 1000000.f + 100.f/7);
    float expected_sum = 1001014300.f;
    float simple_sum = simple_array_sum(vec.data(), n);
    float simple_diff = simple_sum - expected_sum;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    float pairwise_diff = pairwise_sum - expected_sum;
    std::cout << "Simple diff:   " << simple_diff << std::endl;
    std::cout << "Pairwise diff: " << pairwise_diff << std::endl;
}

void test_time() {
    int n = 1000000;
    int repeat = 1000;
    auto begin_simple = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        std::vector<float> vec(n, 1000000.f + 100.f/7);
        simple_array_sum(vec.data(), n);
    }
    auto end_simple = std::chrono::steady_clock::now();
    float time_simple = (float) std::chrono::duration_cast<std::chrono::milliseconds>(end_simple - begin_simple).count();

    auto begin_pairwise = std::chrono::steady_clock::now();
    for (int i = 0; i < repeat; i++) {
        std::vector<float> vec(n, 1000000.f + 100.f/7);
        pairwise_sum_simd(vec.data(), n);
    }
    auto end_pairwise = std::chrono::steady_clock::now();
    float time_pairwise = (float) std::chrono::duration_cast<std::chrono::milliseconds>(end_pairwise - begin_pairwise).count();

    std::cout << "Simple time: " << time_simple / (float) repeat << std::endl;
    std::cout << "Pairwise time: " << time_pairwise / (float) repeat << std::endl;
}

void test_pairwise() {
    std::cout << "\nPairwise tests started" << std::endl;
    test_pairwise_sum_simd();
    test_compare_with_simple();
    test_time();
    std::cout << "Pairwise tests completed\n" << std::endl;
}