//
// PositionTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include <cassert>

#include "UnitTesting.hpp"
#include "Position.hpp"
#include "FEN.hpp"


// MARK: - helpers

bool isMate(std::string fen) {
    Position *pos = FEN::positionFromFEN(fen);
    assert(pos != NULL);
    
    bool ret = pos->isMate();
    delete pos;
    
    return ret;
}

bool isStaleMate(std::string fen) {
    Position *pos = FEN::positionFromFEN(fen);
    assert(pos != NULL);
    
    bool ret = pos->isStaleMate();
    delete pos;
    
    return ret;
}

// MARK: - tests

TEST(Position, basePosition) {
    Position *position = Position::basePosition();
    std::string fen = FEN::FENFromPosition(position);
    delete position;
    CHECK_TRUE(fen == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

TEST(Position, copy) {
    // Checking if a copied position is identical to the source in all properties stored in a FEN.
    std::string originalFEN = "r4k1r/p2n1p1p/1p1N1np1/2pPp3/2P3P1/3B3P/PP3P2/2KR3R b - - 1 18";
    Position *position = FEN::positionFromFEN(originalFEN);
    Position other(*position);
    std::string regenereatedFEN = FEN::FENFromPosition(&other);
    delete position;
    
    CHECK_TRUE(regenereatedFEN == originalFEN);
}

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

TEST(Position, kingPosition) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(position->kingPosition(Color::White) == Square::E1);
    CHECK_TRUE(position->kingPosition(Color::Black) == Square::E8);
}

TEST(Position, kingPositionAfterKingsideCastle) {
    Position *position = FEN::positionFromFEN("r4k1r/p2n1p1p/1p1N1np1/2pPp3/2P3P1/3B3P/PP3P2/R3K2R w KQ - 0 18");
    position->performMove(Move(Square::E1, Square::G1));
    
    CHECK_TRUE(position->kingPosition(Color::White) == Square::G1);
}

TEST(Position, kingPositionAfterQueensideCastle) {
    Position *position = FEN::positionFromFEN("r4k1r/p2n1p1p/1p1N1np1/2pPp3/2P3P1/3B3P/PP3P2/R3K2R w KQ - 0 18");
    position->performMove(Move(Square::E1, Square::C1));
    
    CHECK_TRUE(position->kingPosition(Color::White) == Square::C1);
}

TEST(Position, kingPositionAfterKingMoving) {
    Position *position = FEN::positionFromFEN("r4k1r/p2n1p1p/1p1N1np1/2pPp3/2P3P1/3B3P/PP3P2/2KR3R b - - 1 18");
    position->performMove(Move(Square::F8, Square::G8));
    
    CHECK_TRUE(position->kingPosition(Color::Black) == Square::G8);
}


TEST(Position, isMate) {
    
    CHECK_FALSE(isMate("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
    
    CHECK_TRUE(isMate("rnbqkbnr/ppppp2p/5p2/6pQ/3PP3/8/PPP2PPP/RNB1KBNR b KQkq - 1 3"));
    CHECK_TRUE(isMate("k7/8/8/8/8/8/R7/1R5K b - - 0 1"));
    CHECK_TRUE(isMate("6rk/5Npp/8/8/8/8/8/4K3 b - - 0 1"));
    CHECK_TRUE(isMate("6rk/6pp/6N1/8/8/8/8/4K2R b - - 0 1"));
    CHECK_TRUE(isMate("3rk3/3p4/6B1/2B5/8/8/8/3K4 b - - 0 1"));
}

TEST(Position, isStaleMate) {
    CHECK_FALSE(isStaleMate("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));

    CHECK_TRUE(isStaleMate("3k4/3P4/3K4/8/8/8/8/8 b - - 0 1"));
    CHECK_TRUE(isStaleMate("7k/3PR3/3K4/8/8/8/8/6R1 b - - 0 1"));
    CHECK_TRUE(isStaleMate("4R1nk/3P4/3K4/8/8/8/8/1Q4R1 b - - 0 1"));
    CHECK_TRUE(isStaleMate("2k5/8/1Q1K4/8/8/8/8/8 b - - 0 1"));
}
