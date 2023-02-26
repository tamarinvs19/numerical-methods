#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
# include "../tasks.h"

void test_length() {
    std::cout << "\n=== Length test stated ===" << std::endl;
    int n = 10000000;
    float elem = 10000000.f/std::sqrt(2.f);
    std::vector<float> vec(n, elem);
    assert(length(vec.data(), n) == 10000000.f);
    std::cout << "=== Length test completed successfully ===\n" << std::endl;
}