//
// SquareTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "UnitTesting.hpp"
#include "Square.hpp"

TEST(Square, rowAndCol) {
    for (int c = 0; c < 8; c++) {
        for (int r = 0; r < 8; r++) {
            CHECK_TRUE(Square(c, r).row() == r);
            CHECK_TRUE(Square(c, r).col() == c);
        }
    }
}


TEST(Square, description) {
    CHECK_TRUE(Square::A1.notation() == "a1");
    CHECK_TRUE(Square::B2.notation() == "b2");
    CHECK_TRUE(Square::C3.notation() == "c3");
    CHECK_TRUE(Square::D4.notation() == "d4");
    CHECK_TRUE(Square::E5.notation() == "e5");
}

TEST(Square, addStep) {
    CHECK_TRUE(Square::A1 + Step(1, 0) == Square::B1);
    CHECK_TRUE(Square::A1 + Step(2, 0) == Square::C1);
    CHECK_TRUE(Square::A1 + Step(3, 0) == Square::D1);
    CHECK_TRUE(Square::A1 + Step(1, 1) == Square::B2);
    CHECK_TRUE(Square::A1 + Step(2, 2) == Square::C3);
    CHECK_TRUE(Square::A1 + Step(7, 7) == Square::H8);
    
    CHECK_FALSE((Square::A1 + Step(8, 8)).isValid());
    CHECK_FALSE((Square::A1 + Step(-8, -8)).isValid());
    CHECK_FALSE((Square::C3 + Step(-8, -8)).isValid());
}

TEST(Square, subStep) {
    CHECK_TRUE(Square::H8 - Step(1, 0) == Square::G8);
    CHECK_TRUE(Square::H8 - Step(2, 0) == Square::F8);
    CHECK_TRUE(Square::H8 - Step(3, 0) == Square::E8);
    CHECK_TRUE(Square::H8 - Step(1, 1) == Square::G7);
    CHECK_TRUE(Square::H8 - Step(2, 2) == Square::F6);
    CHECK_TRUE(Square::H8 - Step(7, 7) == Square::A1);
    
    CHECK_FALSE((Square::H8 - Step(8, 8)).isValid());
    CHECK_FALSE((Square::H8 - Step(-8, -8)).isValid());
    CHECK_FALSE((Square::C3 - Step(-8, -8)).isValid());
}

TEST(Square, subSquare) {
    CHECK_TRUE(Square::H8 - Square::G7 == Step(1, 1));
    CHECK_TRUE(Square::G7 - Square::H8 == Step(-1, -1));
}
