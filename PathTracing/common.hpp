#pragma once

#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

static const double MY_PI = 3.14;

static float EPSILON = 0.001;


inline float GetRandomFloat()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> dist(0.f, 1.f); // distribution in range [1, 6]

    return dist(rng);
}

inline float clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}

#endif