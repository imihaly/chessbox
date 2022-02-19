//
// Benchmark.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Benchmark.hpp"

#ifdef _MSC_VER
#   include "windows.h"
long int millis() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    WORD millis = (time.wSeconds * 1000) + time.wMilliseconds;
    return millis;
}

long int usecs() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    WORD usecs = (time.wSeconds * 1000000) + time.wMilliseconds * 1000;
    return usecs;
}
#else
#   include <sys/time.h>
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
#endif

std::map<std::string, Benchmark* > Benchmark::benchmarks;
std::vector<Benchmark* > Benchmark::orderedBenchmarks;

long int Benchmark::referenceValue = 0;
