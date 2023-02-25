#include <cassert>
#include <iostream>
#include <vector>
#include "../tasks.h"

void test_statistics() {
    std::cout << "Start statistics test" << std::endl;
    Statistics statistics;

    std::vector<float> values = {10, 20, 30, 40};
    for (auto elem: values) {
        statistics.update(elem);
    }

    assert(statistics.count() == 4);
    assert(statistics.min() == 10.f);
    assert(statistics.max() == 40.f);
    assert(statistics.sum() == 100.f);
    assert(statistics.mean() == 25.f);
    assert(statistics.variance() == 125.f);
    std::cout << "Start statistics completed successfully" << std::endl;
}