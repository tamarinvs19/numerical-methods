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

void test_pairwise_simple_even_1() {
    int n = 4;
    std::vector<float> vec(n, 10.5);
    float expected_sum = 42;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple even test #1 completed" << std::endl;
}

void test_pairwise_simple_even_2() {
    int n = 6;
    std::vector<float> vec(n, 10);
    float expected_sum = 60;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple even test #2 completed" << std::endl;
}

void test_pairwise_simple_even_3() {
    int n = 2;
    std::vector<float> vec(n, 10);
    float expected_sum = 20;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple even test #3 completed" << std::endl;
}

void test_pairwise_simple_odd_1() {
    int n = 3;
    std::vector<float> vec(n, 10);
    float expected_sum = 30;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple odd test #1 completed" << std::endl;
}

void test_pairwise_simple_odd_2() {
    int n = 7;
    std::vector<float> vec(n, 10);
    float expected_sum = 70;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple odd test #2 completed" << std::endl;
}

void test_pairwise_simple_odd_3() {
    int n = 1;
    std::vector<float> vec(n, 10);
    float expected_sum = 10;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd simple odd test #3 completed" << std::endl;
}

void test_pairwise_sum_simd_1() {
    int n = 1002;
    std::vector<float> vec(n, 10000.f + 1.f/3);
    float expected_sum = 10020334.f;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd test #1 completed" << std::endl;
}

void test_pairwise_sum_simd_2() {
    int n = 1001000;
    std::vector<float> vec(n, 10.f/7);
    float expected_sum = 1430000.f;
    float pairwise_sum = pairwise_sum_simd(vec.data(), n);
    assert(pairwise_sum == expected_sum);
    std::cout << "Pairwise sum simd test #2 completed" << std::endl;
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
    std::cout << "\n=== Pairwise tests started ===" << std::endl;
    test_pairwise_simple_even_1();
    test_pairwise_simple_even_2();
    test_pairwise_simple_even_3();
    test_pairwise_simple_odd_1();
    test_pairwise_simple_odd_2();
    test_pairwise_simple_odd_3();
    test_pairwise_sum_simd_1();
    test_pairwise_sum_simd_2();
    test_compare_with_simple();
    test_time();
    std::cout << "=== Pairwise tests completed ===\n" << std::endl;
}