cmake_minimum_required(VERSION 3.24)
project(homework1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

add_executable(homework1 tasks.h main.cpp polynomial.cpp kahan_sum.cpp statistics.cpp length.cpp pairwise_sum_simd.cpp)
