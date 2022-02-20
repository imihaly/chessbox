//
// GeometryTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "Geometry.hpp"
#include "UnitTesting.hpp"
#include <array>

#pragma mark - testing pawn control

TEST(Geometry, directions) {
    
    CHECK_TRUE(Direction::North ==  Geometry::dir(Square::A1, Square::A8));
    CHECK_TRUE(Direction::North ==  Geometry::dir(Square::A1, Square::A2));
    CHECK_TRUE(Direction::North ==  Geometry::dir(Square::H1, Square::H3));
    CHECK_TRUE(Direction::North ==  Geometry::dir(Square::H7, Square::H8));

    CHECK_TRUE(Direction::South ==  Geometry::dir(Square::A8, Square::A7));
    CHECK_TRUE(Direction::South ==  Geometry::dir(Square::B7, Square::B5));
    CHECK_TRUE(Direction::South ==  Geometry::dir(Square::C6, Square::C3));
    CHECK_TRUE(Direction::South ==  Geometry::dir(Square::D5, Square::D1));

    CHECK_TRUE(Direction::West ==  Geometry::dir(Square::H5, Square::E5));
    CHECK_TRUE(Direction::West ==  Geometry::dir(Square::B4, Square::A4));
    CHECK_TRUE(Direction::West ==  Geometry::dir(Square::C6, Square::A6));
    CHECK_TRUE(Direction::West ==  Geometry::dir(Square::D5, Square::B5));

    CHECK_TRUE(Direction::East ==  Geometry::dir(Square::G5, Square::H5));
    CHECK_TRUE(Direction::East ==  Geometry::dir(Square::B4, Square::H4));
    CHECK_TRUE(Direction::East ==  Geometry::dir(Square::C6, Square::E6));
    CHECK_TRUE(Direction::East ==  Geometry::dir(Square::D5, Square::G5));

    CHECK_TRUE(Direction::NorthEast ==  Geometry::dir(Square::G5, Square::H6));
    CHECK_TRUE(Direction::NorthEast ==  Geometry::dir(Square::B4, Square::D6));
    CHECK_TRUE(Direction::NorthEast ==  Geometry::dir(Square::C6, Square::E8));
    CHECK_TRUE(Direction::NorthEast ==  Geometry::dir(Square::D5, Square::G8));

    CHECK_TRUE(Direction::SouthEast ==  Geometry::dir(Square::G5, Square::H4));
    CHECK_TRUE(Direction::SouthEast ==  Geometry::dir(Square::B4, Square::D2));
    CHECK_TRUE(Direction::SouthEast ==  Geometry::dir(Square::C6, Square::H1));
    CHECK_TRUE(Direction::SouthEast ==  Geometry::dir(Square::D5, Square::G2));

    CHECK_TRUE(Direction::NorthWest ==  Geometry::dir(Square::G5, Square::D8));
    CHECK_TRUE(Direction::NorthWest ==  Geometry::dir(Square::B4, Square::A5));
    CHECK_TRUE(Direction::NorthWest ==  Geometry::dir(Square::C6, Square::A8));
    CHECK_TRUE(Direction::NorthWest ==  Geometry::dir(Square::D5, Square::B7));

    CHECK_TRUE(Direction::SouthWest ==  Geometry::dir(Square::G5, Square::D2));
    CHECK_TRUE(Direction::SouthWest ==  Geometry::dir(Square::B4, Square::A3));
    CHECK_TRUE(Direction::SouthWest ==  Geometry::dir(Square::C6, Square::A4));
    CHECK_TRUE(Direction::SouthWest ==  Geometry::dir(Square::D5, Square::A2));

    CHECK_TRUE(Direction::Any ==  Geometry::dir(Square::A2, Square::A2));
    CHECK_TRUE(Direction::Any ==  Geometry::dir(Square::E4, Square::E4));

    CHECK_TRUE(Direction::Unknown ==  Geometry::dir(Square::A2, Square::H3));
    CHECK_TRUE(Direction::Unknown ==  Geometry::dir(Square::E4, Square::D8));
}


TEST(Geometry, pawnCaptures) {
    Squares expected = Squares(0);
    
    expected = Geometry::bitboard(Square::B3);
    CHECK_TRUE(Geometry::pawnCaptures(Square::A2, Color::White) == expected);
    
    expected = Geometry::bitboard(Square::A3);
    expected.add(Square::C3);
    CHECK_TRUE(Geometry::pawnCaptures(Square::B2, Color::White) ==  expected);

    expected = Geometry::bitboard(Square::A1);
    expected.add(Square::C1);
    CHECK_TRUE(Geometry::pawnCaptures(Square::B2, Color::Black) ==  expected);
}

TEST(Geometry, tillFirstByDir) {
    
    Squares squares = Geometry::tillFirstByDir(Square::A1, Direction::NorthEast, ~Geometry::allSquares);
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
    
    Squares squares = Geometry::tillFirstByDir(Square::B2, Direction::NorthEast, Geometry::file(5));
    Squares expected = 0;
    expected.add(Square::C3);
    expected.add(Square::D4);
    expected.add(Square::E5);
    expected.add(Square::F6);

    CHECK_TRUE(squares == expected);
}

