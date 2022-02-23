//
// Benchmark.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Benchmark_hpp
#define Benchmark_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <cassert>
#include <climits>

long int millis();
long int usecs();

struct Benchmark {
    static std::map<std::string, Benchmark* > benchmarks;
    static std::vector<Benchmark* > orderedBenchmarks;
        
    static void reg(std::string name, long int value, long int refVal) {
        if (benchmarks.find(name) == benchmarks.end()) {
            Benchmark *benchmark = new Benchmark(name, refVal);
            benchmarks[name] = benchmark;
            orderedBenchmarks.push_back(benchmark);
        }
        benchmarks[name]->reg(value);
    }
        
    static void printAll() {
        for(auto it = orderedBenchmarks.begin(); it != orderedBenchmarks.end(); ++it) {
            (*it)->print();
        }
    }

    static bool checkAll() {
        bool success = true;
        for(auto it = orderedBenchmarks.begin(); it != orderedBenchmarks.end(); ++it) {
            if(! (*it)->CHECK_TRUE() ) success = false;
        }
        return success;
    }

    
    std::string name;
    long int min, max, count, sum, refVal;
    
    Benchmark(std::string name = "", long int refVal = 0): name(name), min(LONG_MAX), max(0), count(0), sum(0), refVal(refVal) {};
    void reg(long int value) {
        count++;
        sum += value;
        if (value < min) min = value;
        if (value > max) max = value;
    }
    
    void print() {
        long int avg = count ? sum / count : 0;
        std::cout << name << ": " << min << "/" << avg << "/" << max << " - from: " << count << std::endl;
    }
    
    std::string truncate(std::string input, int width) {
        std::string str = input;
        if (str.length() > width) {
            str.resize(width - 3);
            return str.append("...");
        } else {
            str.resize(width, ' ');
        }
        return str;
    }
    
    bool CHECK_TRUE() {
        assert(referenceValue);
        assert(refVal);
        long int avg = count ? sum / count : 0;
        bool succeed = avg < refVal;
        long percent = (refVal - avg) * 100 / avg;
        
        std::cout << (succeed ? "[🟢] " : "[🔴] " )
            << std::setw(4) << percent << "% "
            << "/"
            << std::setw(8) << 1.0 * avg
            << "   " << truncate(name, 40) << ": "
            << min << "/" << avg << "/" << max
        << std::endl;
        
        return succeed;
    }

};


#define BENCHMARK(name, refVal) for(long int start = usecs(), run = 1; run; run=0, Benchmark::reg(name, usecs() - start, refVal))


#endif /* Benchmark_hpp */
