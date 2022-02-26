//
// SquaresTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Squares.hpp"
#include "UnitTesting.hpp"

TEST(Squares, addSquare) {
    Squares squares = UnitTesting::squaresFromFEN("8/8/8/8/8/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("8/8/8/8/4P3/8/8/8 w - - 0 1");

    squares.add(Square::E4);

    CHECK_TRUE(squares == expected);
}

TEST(Squares, removeSquare) {
    Squares squares = UnitTesting::squaresFromFEN("8/8/8/8/4P3/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("8/8/8/8/8/8/8/8 w - - 0 1");

    squares.remove(Square::E4);
    CHECK_TRUE(squares == expected);
}

TEST(Squares, orSquare) {
    Squares squares = UnitTesting::squaresFromFEN("7P/6P1/5P2/4P3/3P4/2P5/1P6/P7 w - - 0 1");
    Squares other = UnitTesting::squaresFromFEN("P1P1P1P1/1P1P1P1P/P2P2P1/1P2P2P/P3P3/1P3P2/2P3P1/3P3P w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("P1P1P1PP/1P1P1PPP/P2P1PP1/1P2P2P/P2PP3/1PP2P2/1PP3P1/P2P3P w - - 0 1");

    squares |= other;
    CHECK_TRUE(squares == expected);
}

TEST(Squares, andSquare) {
    Squares squares = UnitTesting::squaresFromFEN("7P/6P1/5P2/4P3/3P4/2P5/1P6/P7 w - - 0 1");
    Squares other = UnitTesting::squaresFromFEN("P1P1P1P1/1P1P1P1P/P2P2P1/1P2P2P/P3P3/1P3P2/2P3P1/3P3P w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("8/8/8/4P3/8/8/8/8 w - - 0 1");

    squares &= other;
    CHECK_TRUE(squares == expected);
}

TEST(Squares, xorSquare) {
    Squares squares = UnitTesting::squaresFromFEN("7P/6P1/5P2/4P3/3P4/2P5/1P6/P7 w - - 0 1");
    Squares other = UnitTesting::squaresFromFEN("P1P1P1P1/1P1P1P1P/P2P2P1/1P2P2P/P3P3/1P3P2/2P3P1/3P3P w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("P1P1P1PP/1P1P1PPP/P2P1PP1/1P5P/P2PP3/1PP2P2/1PP3P1/P2P3P w - - 0 1");

    squares ^= other;
    CHECK_TRUE(squares == expected);
}

TEST(Squares, negSquare) {
    Squares squares = UnitTesting::squaresFromFEN("7P/6P1/5P2/4P3/3P4/2P5/1P6/P7 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("PPPPPPP1/PPPPPP1P/PPPPP1PP/PPPP1PPP/PPP1PPPP/PP1PPPPP/P1PPPPPP/1PPPPPPP w - - 0 1");

    CHECK_TRUE(~squares == expected);
}
