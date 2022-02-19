//
// main.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include <iostream>
#include "ChessBasics.hpp"
#include "Benchmark.hpp"
#include <vector>
#include <fstream>
#include <random>

using namespace chessbox;
using TestValueType = char;

struct TestVal {
    TestValueType val;
    TestVal(TestValueType v): val(v) {}
    TestVal operator+(const TestVal& other) { return TestVal(val+other.val); }
    TestVal& operator+=(const TestVal& other) { val += other.val; return *this; }
};

int main(int argc, const char * argv[]) {
    std::string fen =
     // "K1k5/8/P7/8/8/8/8/8 w - - 0 1"; // 1.5 -> 0.33; 0.9; 0.73; 0.72; 0.7; 0.66; 0.62; 0.60; 0.55; 0.368; 0.33; 0.27; 0.26; 0.23
    "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0"; // 3.5 -> 3.1; 2.8; 2.38; 2.35; 2.27; 2.23; 2.12; 2.11; 1.95; 1.56; 1.50; 1.37; 1.29; 1.23; 1.20
    //"4k3/1P6/8/8/8/8/K7/8 w - - 0 1"; // -> 0.809; 0.504
    //"r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"; // -> 2.762; 0.9

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<uint64_t> dist(0, 0xffffffffffffffffull);
    
    BENCHMARK_CALIBRATE() {
        Squares a;
        Squares b(0xaaaaaaaaaaaaaaaa);
        Squares c(0x5555555555555555);
        Squares d(0xffffffffffffffff);
        for(int idx = 0; idx < 1000000; idx++) {
            a = dist(mt);
            a |= ~b;
            a ^= ~c;
            a &= ~d;
        }
    }


    int count = 1000000;
    Moves moves;
#if 1
    fen = "K1k5/8/P7/8/8/8/8/8 w - - 0 1";
    Position* position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 50) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 670) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "4k3/1P6/8/8/8/8/K7/8 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 70) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 570) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

#else

    count = 10000000;
    BENCHMARK(std::string("primitive: "), 570) {
        TestValueType v = 0;
        for(int idx = 0; idx < count; idx++) {
            v = v + TestValueType(rand());
        }
    }
    
    BENCHMARK(std::string("struct: "), 570) {
        TestVal v = 0;
        for(int idx = 0; idx < count; idx++) {
            v = v + TestVal(rand());
        }
    }


#endif

    Benchmark::checkAll();
    return 0;
}
