//
// GeometryTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "BB.hpp"
#include "UnitTesting.hpp"
#include <array>

// MARK: - testing pawn control

TEST(Geometry, directions) {
    
    CHECK_TRUE(Direction::North ==  BB::dir(Square::A1, Square::A8));
    CHECK_TRUE(Direction::North ==  BB::dir(Square::A1, Square::A2));
    CHECK_TRUE(Direction::North ==  BB::dir(Square::H1, Square::H3));
    CHECK_TRUE(Direction::North ==  BB::dir(Square::H7, Square::H8));

    CHECK_TRUE(Direction::South ==  BB::dir(Square::A8, Square::A7));
    CHECK_TRUE(Direction::South ==  BB::dir(Square::B7, Square::B5));
    CHECK_TRUE(Direction::South ==  BB::dir(Square::C6, Square::C3));
    CHECK_TRUE(Direction::South ==  BB::dir(Square::D5, Square::D1));

    CHECK_TRUE(Direction::West ==  BB::dir(Square::H5, Square::E5));
    CHECK_TRUE(Direction::West ==  BB::dir(Square::B4, Square::A4));
    CHECK_TRUE(Direction::West ==  BB::dir(Square::C6, Square::A6));
    CHECK_TRUE(Direction::West ==  BB::dir(Square::D5, Square::B5));

    CHECK_TRUE(Direction::East ==  BB::dir(Square::G5, Square::H5));
    CHECK_TRUE(Direction::East ==  BB::dir(Square::B4, Square::H4));
    CHECK_TRUE(Direction::East ==  BB::dir(Square::C6, Square::E6));
    CHECK_TRUE(Direction::East ==  BB::dir(Square::D5, Square::G5));

    CHECK_TRUE(Direction::NorthEast ==  BB::dir(Square::G5, Square::H6));
    CHECK_TRUE(Direction::NorthEast ==  BB::dir(Square::B4, Square::D6));
    CHECK_TRUE(Direction::NorthEast ==  BB::dir(Square::C6, Square::E8));
    CHECK_TRUE(Direction::NorthEast ==  BB::dir(Square::D5, Square::G8));

    CHECK_TRUE(Direction::SouthEast ==  BB::dir(Square::G5, Square::H4));
    CHECK_TRUE(Direction::SouthEast ==  BB::dir(Square::B4, Square::D2));
    CHECK_TRUE(Direction::SouthEast ==  BB::dir(Square::C6, Square::H1));
    CHECK_TRUE(Direction::SouthEast ==  BB::dir(Square::D5, Square::G2));

    CHECK_TRUE(Direction::NorthWest ==  BB::dir(Square::G5, Square::D8));
    CHECK_TRUE(Direction::NorthWest ==  BB::dir(Square::B4, Square::A5));
    CHECK_TRUE(Direction::NorthWest ==  BB::dir(Square::C6, Square::A8));
    CHECK_TRUE(Direction::NorthWest ==  BB::dir(Square::D5, Square::B7));

    CHECK_TRUE(Direction::SouthWest ==  BB::dir(Square::G5, Square::D2));
    CHECK_TRUE(Direction::SouthWest ==  BB::dir(Square::B4, Square::A3));
    CHECK_TRUE(Direction::SouthWest ==  BB::dir(Square::C6, Square::A4));
    CHECK_TRUE(Direction::SouthWest ==  BB::dir(Square::D5, Square::A2));

    CHECK_TRUE(Direction::Any ==  BB::dir(Square::A2, Square::A2));
    CHECK_TRUE(Direction::Any ==  BB::dir(Square::E4, Square::E4));

    CHECK_TRUE(Direction::Unknown ==  BB::dir(Square::A2, Square::H3));
    CHECK_TRUE(Direction::Unknown ==  BB::dir(Square::E4, Square::D8));
}


TEST(Geometry, pawnCaptures) {
    Squares expected = Squares(0);
    
    expected = BB::bitboard(Square::B3);
    CHECK_TRUE(BB::pawnCaptures(Square::A2, Color::White) == expected);
    
    expected = BB::bitboard(Square::A3);
    expected.add(Square::C3);
    CHECK_TRUE(BB::pawnCaptures(Square::B2, Color::White) ==  expected);

    expected = BB::bitboard(Square::A1);
    expected.add(Square::C1);
    CHECK_TRUE(BB::pawnCaptures(Square::B2, Color::Black) ==  expected);
}

TEST(Geometry, tillFirstByDir) {
    
    Squares squares = BB::tillFirstByDir(Square::A1, Direction::NorthEast, ~BB::allSquares);
    Squares expected = 0;
    expected.add(Square::B2);
    expected.add(Square::C3);
    expected.add(Square::D4);
    expected.add(Square::E5);
    expected.add(Square::F6);
    expected.add(Square::G7);
    expected.add(Square::H8);

    CHECK_TRUE(squares == expected);
}
TEST(Geometry, tillFirstByDir2) {
    
    Squares squares = BB::tillFirstByDir(Square::B2, Direction::NorthEast, BB::file(5));
    Squares expected = 0;
    expected.add(Square::C3);
    expected.add(Square::D4);
    expected.add(Square::E5);
    expected.add(Square::F6);

    CHECK_TRUE(squares == expected);
}

