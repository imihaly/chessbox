//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
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

    
    std::string fen = "7K/8/5k2/8/8/8/8/8 w - - 0 1";
    Position* position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 0.2) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }
    
    fen = "2k5/2P5/3K4/8/8/8/8/8 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 0.3) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "8/8/8/3k4/8/5K2/8/8 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 0.3) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }
    
    fen = "8/8/8/3k4/4N3/5K2/8/8 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 0.6) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "r4k1r/p2n1p1p/1p1N1np1/2pPp3/2P3P1/3B3P/PP3P2/R3K2R w KQ - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 2.0) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "r1bq1rk1/pp2n1bp/2pp1np1/3PppN1/1PP1P3/2N2B2/P4PPP/R1BQR1K1 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 2) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "rn3rk1/ppp4p/3b1p2/3PNb1q/2BP1Bp1/2N3P1/PPPQ4/R5K1 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 2) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    fen = "4R3/2Q5/6R1/1K1B1N2/3B4/3N4/P6P/1k6 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 5) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }
    
    fen = "R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1";
    position = FEN::positionFromFEN(fen);
    BENCHMARK(std::string("allMoves: ") + fen, 9) {
        for(int idx = 0; idx < count; idx++) {
            moves.clear();
            Movegen::allMoves(position, moves);
        }
    }

    if (!Benchmark::checkAll()) return -1;
    return 0;
}
