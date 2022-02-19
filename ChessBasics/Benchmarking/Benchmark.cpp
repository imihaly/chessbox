//
// Benchmark.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Benchmark.hpp"

std::map<std::string, Benchmark* > Benchmark::benchmarks;
std::vector<Benchmark* > Benchmark::orderedBenchmarks;

long int Benchmark::referenceValue = 0;

long int millis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
}

long int usecs() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}
