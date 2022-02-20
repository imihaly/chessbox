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
    Squares squares = UnitTesting::squaresFromString(
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                           );
    
    Squares expected = UnitTesting::squaresFromString(
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "....x..."
                                                     "........"
                                                     "........"
                                                     "........"
                                                           );

    squares.add(Square::E4);
    CHECK_TRUE(squares == expected);
}

TEST(Squares, removeSquare) {
    Squares squares = UnitTesting::squaresFromString(
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "....x..."
                                                     "........"
                                                     "........"
                                                     "........"
                                                           );
    
    Squares expected = UnitTesting::squaresFromString(
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                     "........"
                                                           );

    squares.remove(Square::E4);
    CHECK_TRUE(squares == expected);
}

TEST(Squares, orSquare) {
    Squares squares = UnitTesting::squaresFromString(
                                                     ".......x"
                                                     "......x."
                                                     ".....x.."
                                                     "....x..."
                                                     "...x...."
                                                     "..x....."
                                                     ".x......"
                                                     "x......."
                                                           );
    Squares other = UnitTesting::squaresFromString(
                                                     "x.x.x.x."
                                                     ".x.x.x.x"
                                                     "x..x..x."
                                                     ".x..x..x"
                                                     "x...x..."
                                                     ".x...x.."
                                                     "..x...x."
                                                     "...x...x"
                                                           );

    Squares expected = UnitTesting::squaresFromString(
                                                      "x.x.x.xx"
                                                      ".x.x.xxx"
                                                      "x..x.xx."
                                                      ".x..x..x"
                                                      "x..xx..."
                                                      ".xx..x.."
                                                      ".xx...x."
                                                      "x..x...x"
                                                           );

    squares |= other;
    CHECK_TRUE(squares == expected);
}

TEST(Squares, andSquare) {
    Squares squares = UnitTesting::squaresFromString(
                                                     ".......x"
                                                     "......x."
                                                     ".....x.."
                                                     "....x..."
                                                     "...x...."
                                                     "..x....."
                                                     ".x......"
                                                     "x......."
                                                           );
    Squares other = UnitTesting::squaresFromString(
                                                     "x.x.x.x."
                                                     ".x.x.x.x"
                                                     "x..x..x."
                                                     ".x..x..x"
                                                     "x...x..."
                                                     ".x...x.."
                                                     "..x...x."
                                                     "...x...x"
                                                           );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "....x..."
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                           );

    squares &= other;
    CHECK_TRUE(squares == expected);
}

TEST(Squares, xorSquare) {
    Squares squares = UnitTesting::squaresFromString(
                                                     ".......x"
                                                     "......x."
                                                     ".....x.."
                                                     "....x..."
                                                     "...x...."
                                                     "..x....."
                                                     ".x......"
                                                     "x......."
                                                           );
    Squares other = UnitTesting::squaresFromString(
                                                     "x.x.x.x."
                                                     ".x.x.x.x"
                                                     "x..x..x."
                                                     ".x..x..x"
                                                     "x...x..."
                                                     ".x...x.."
                                                     "..x...x."
                                                     "...x...x"
                                                           );

    Squares expected = UnitTesting::squaresFromString(
                                                      "x.x.x.xx"
                                                      ".x.x.xxx"
                                                      "x..x.xx."
                                                      ".x.....x"
                                                      "x..xx..."
                                                      ".xx..x.."
                                                      ".xx...x."
                                                      "x..x...x"
                                                           );

    squares ^= other;
    CHECK_TRUE(squares == expected);
}

TEST(Squares, negSquare) {
    Squares squares = UnitTesting::squaresFromString(
                                                     ".......x"
                                                     "......x."
                                                     ".....x.."
                                                     "....x..."
                                                     "...x...."
                                                     "..x....."
                                                     ".x......"
                                                     "x......."
                                                           );
    Squares expected = UnitTesting::squaresFromString(
                                                      "xxxxxxx."
                                                      "xxxxxx.x"
                                                      "xxxxx.xx"
                                                      "xxxx.xxx"
                                                      "xxx.xxxx"
                                                      "xx.xxxxx"
                                                      "x.xxxxxx"
                                                      ".xxxxxxx"
                                                           );

    CHECK_TRUE(~squares == expected);
}
