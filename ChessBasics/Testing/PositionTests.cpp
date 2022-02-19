//
// PositionTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "UnitTesting.hpp"
#include "Position.hpp"
#include "FEN.hpp"

TEST(Position, performMove) {
    struct TestData {
        std::string startFen;
        Move move;
        std::string endFen;
    };
    
    TestData testData[] = {
        // Ruy-Lopez
        {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", /* 1. e4 */ Move(Square::E2, Square::E4), "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"},
        {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1", /* 1... e5 */ Move(Square::E7, Square::E5), "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2"},
        {"rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2", /* 2. Nf3 */ Move(Square::G1, Square::F3), "rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"},
        {"rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2", /* 2... Nc6 */ Move(Square::B8, Square::C6), "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3"},
        {"r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3", /* 3. Bb5 */ Move(Square::F1, Square::B5), "r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 3 3"},
        {"r1bqkbnr/pppp1ppp/2n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 3 3", /* 3... a6 */ Move(Square::A7, Square::A6), "r1bqkbnr/1ppp1ppp/p1n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4"},
        {"r1bqkbnr/1ppp1ppp/p1n5/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 0 4", /* 4. Ba4 */ Move(Square::B5, Square::A4), "r1bqkbnr/1ppp1ppp/p1n5/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 1 4" },
        {"r1bqkbnr/1ppp1ppp/p1n5/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 1 4", /* 4... Nf6 */ Move(Square::G8, Square::F6), "r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5"},
        {"r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 5", /* 5. 0-0 */ Move(Square::E1, Square::G1), "r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 3 5"},
        
        // random positions
        {"r1q2rk1/1bp1nppp/p2p1b2/1p1Bp3/4P3/2PP1N2/PP1B1PPP/R2QR1K1 w - - 1 14", /* 14. Bxb7 */ Move(Square::D5, Square::B7), "r1q2rk1/1Bp1nppp/p2p1b2/1p2p3/4P3/2PP1N2/PP1B1PPP/R2QR1K1 b - - 0 14"},
        {"rnbqkbnr/pp1p1ppp/8/2pPp3/8/8/PPP1PPPP/RNBQKBNR w KQkq e6 0 3", /* en-passant */ Move(Square::D5, Square::E6), "rnbqkbnr/pp1p1ppp/4P3/2p5/8/8/PPP1PPPP/RNBQKBNR b KQkq - 0 3"}
    };
    
    for(TestData testCase: testData) {
        Position *pos = FEN::positionFromFEN(testCase.startFen);
        assert(pos);
        
        pos->makeMove(testCase.move);
        
        CHECK_TRUE(testCase.endFen == FEN::FENFromPosition(pos));
        delete pos;
    }
}


