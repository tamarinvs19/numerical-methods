//
// Created by vyacheslav on 24.02.23.
//

#ifndef HOMEWORK1_TASKS_H
#define HOMEWORK1_TASKS_H

float polynomial(float x, const float* a, int n);

float kahan_sum(const float* x, int n);

float pairwise_sum_simd(float* x, int n);

class Statistics {
    int length = 0;
    float currentMin = 0;
    float currentMax = 0;
    float currentSum = 0;
    float currentMean = 0;
    float sumVarM = 0;
public:
    void update(float x);            // добавить новый элемент
    int count() const noexcept;
    float min() const noexcept;
    float max() const noexcept;
    float sum() const noexcept;
    float mean() const noexcept;     // среднее
    float variance() const noexcept; // дисперсия
};

float length(const float* x, int n);

#endif //HOMEWORK1_TASKS_H
