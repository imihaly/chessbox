//
// main.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include <iostream>
#include <vector>
#include <fstream>
#include <random>

#include "chessbox.hpp"
#include "Benchmark.hpp"

using namespace chessbox;
int main(int argc, const char * argv[]) {

    int count = 1000000;
    Moves moves;

    std::string fen = "K1k5/8/P7/8/8/8/8/8 w - - 0 1";
    Position* position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 0.15) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 2.5) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "4k3/1P6/8/8/8/8/K7/8 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 0.25) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 2.5) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }


    if (!Benchmark::checkAll()) return -1;
    return 0;
}
