//
// Benchmark.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Benchmark.hpp"
#include <chrono>

long int millis() {
    uint64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch())
    .count();
    return ms;
}

long int usecs() {
    uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch())
    .count();
    return us;
}

std::map<std::string, Benchmark* > Benchmark::benchmarks;
std::vector<Benchmark* > Benchmark::orderedBenchmarks;

long int Benchmark::referenceValue = 0;
