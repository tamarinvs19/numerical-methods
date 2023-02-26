#include <cassert>
#include <iostream>
#include "../tasks.h"


void test_polynomial_1() {
    int n = 3;
    float x = 2;
    const float a[3] = {3, 5, 7};
    assert(polynomial(x, a, n) == 41);
}

void test_polynomial_2() {
    int n = 3;
    float x = 4;
    const float a[3] = {0, 0, 1};
    assert(polynomial(x, a, n) == 16);
}


void test_polynomial_zero_deg() {
    int n = 1;
    float x = 2;
    const float a[1] = {5};
    assert(polynomial(x, a, n) == 5);
}

void test_polynomial() {
    std::cout << "\n=== Test polynomial started ===" << std::endl;
    test_polynomial_1();
    test_polynomial_2();
    test_polynomial_zero_deg();
    std::cout << "=== Test polynomial completed successfully ===\n" << std::endl;
}