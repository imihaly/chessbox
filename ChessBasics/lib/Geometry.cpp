//
// Geometry.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Geometry.hpp"
#include "bitscan.hpp"

#pragma mark - square

#include "Generators/SquareGenerator.hpp"

constexpr std::array<BitBoard, 64> squaresTable = BBSquaresTableGenerator<>::table;

const BitBoard Geometry::bitboard(const Square square) {
    return squaresTable[(int)square];
}

#pragma mark - rank

#include "Generators/RankGenerator.hpp"

static constexpr BitBoard ranksTable[] = {
    BBRankGenerator<0>::v, BBRankGenerator<1>::v, BBRankGenerator<2>::v, BBRankGenerator<3>::v, BBRankGenerator<4>::v, BBRankGenerator<5>::v, BBRankGenerator<6>::v, BBRankGenerator<7>::v
};

const BitBoard Geometry::rank(int rankIdx) {
    return ranksTable[rankIdx];
}

#pragma mark - file

#include "Generators/FileGenerator.hpp"

static const BitBoard filesTable[] = {
    BBFileGenerator<0>::v, BBFileGenerator<1>::v, BBFileGenerator<2>::v, BBFileGenerator<3>::v, BBFileGenerator<4>::v, BBFileGenerator<5>::v, BBFileGenerator<6>::v, BBFileGenerator<7>::v
};

const BitBoard Geometry::file(int fileIdx) {
    return filesTable[fileIdx];
}

#pragma mark - adjacent

#include "Generators/AdjacentsGenerator.hpp"

constexpr std::array<BitBoard, 512> adjacentsPerDirectionTable = BBAdjacentsPerDirectionTableGenerator<>::table;

const BitBoard Geometry::adjacent(const Square square, Direction dir) {
    return adjacentsPerDirectionTable[(int)square * 8 + dir];
}

constexpr std::array<BitBoard, 64> adjacentsTable = BBAdjacentsTableGenerator<>::table;

const BitBoard Geometry::adjacents(const Square square) {
    return adjacentsTable[(int)square];
}

#pragma mark - lines

#include "Generators/LinesGenerator.hpp"

constexpr std::array<BitBoard, 512> lineTable = BBLinesTableGenerator<>::table;
constexpr std::array<BitBoard, 64> rookLineTable = BBRookLinesTableGenerator<>::table;
constexpr std::array<BitBoard, 64> bishopLinesTable = BBBishopLinesTableGenerator<>::table;

const BitBoard Geometry::line(const Square square, Direction dir) {
    return lineTable[(int)square * 8 + dir];
}

const BitBoard Geometry::lines(const Square square) {
    return lineTable[(int)square * 8 + Direction::North] |
    lineTable[(int)square * 8 + Direction::NorthEast] |
    lineTable[(int)square * 8 + Direction::East] |
    lineTable[(int)square * 8 + Direction::SouthEast] |
    lineTable[(int)square * 8 + Direction::South] |
    lineTable[(int)square * 8 + Direction::SouthWest] |
    lineTable[(int)square * 8 + Direction::West] |
    lineTable[(int)square * 8 + Direction::NorthWest];
}

const BitBoard Geometry::rookLines(const Square square) {
    return rookLineTable[(int)square];
}

const BitBoard Geometry::bishopLines(const Square square) {
    return bishopLinesTable[(int)square];
}

#pragma mark - directions defined by 2 squares

#include "Generators/DirectionsGenerator.hpp"

//constexpr std::array<Direction, 64 * 64> directionsTable = BBDirectionsTableGenerator<>::table;

constexpr std::array<std::array<Direction, 64>, 64> directionsTable = {
    BBDirectionsSubTableGenerator<0>::v,
    BBDirectionsSubTableGenerator<1>::v,
    BBDirectionsSubTableGenerator<2>::v,
    BBDirectionsSubTableGenerator<3>::v,
    BBDirectionsSubTableGenerator<4>::v,
    BBDirectionsSubTableGenerator<5>::v,
    BBDirectionsSubTableGenerator<6>::v,
    BBDirectionsSubTableGenerator<7>::v,

    BBDirectionsSubTableGenerator<8>::v,
    BBDirectionsSubTableGenerator<9>::v,
    BBDirectionsSubTableGenerator<10>::v,
    BBDirectionsSubTableGenerator<11>::v,
    BBDirectionsSubTableGenerator<12>::v,
    BBDirectionsSubTableGenerator<13>::v,
    BBDirectionsSubTableGenerator<14>::v,
    BBDirectionsSubTableGenerator<15>::v,

    BBDirectionsSubTableGenerator<16>::v,
    BBDirectionsSubTableGenerator<17>::v,
    BBDirectionsSubTableGenerator<18>::v,
    BBDirectionsSubTableGenerator<19>::v,
    BBDirectionsSubTableGenerator<20>::v,
    BBDirectionsSubTableGenerator<21>::v,
    BBDirectionsSubTableGenerator<22>::v,
    BBDirectionsSubTableGenerator<23>::v,

    BBDirectionsSubTableGenerator<24>::v,
    BBDirectionsSubTableGenerator<25>::v,
    BBDirectionsSubTableGenerator<26>::v,
    BBDirectionsSubTableGenerator<27>::v,
    BBDirectionsSubTableGenerator<28>::v,
    BBDirectionsSubTableGenerator<29>::v,
    BBDirectionsSubTableGenerator<30>::v,
    BBDirectionsSubTableGenerator<31>::v,

    BBDirectionsSubTableGenerator<32>::v,
    BBDirectionsSubTableGenerator<33>::v,
    BBDirectionsSubTableGenerator<34>::v,
    BBDirectionsSubTableGenerator<35>::v,
    BBDirectionsSubTableGenerator<36>::v,
    BBDirectionsSubTableGenerator<37>::v,
    BBDirectionsSubTableGenerator<38>::v,
    BBDirectionsSubTableGenerator<39>::v,

    BBDirectionsSubTableGenerator<40>::v,
    BBDirectionsSubTableGenerator<41>::v,
    BBDirectionsSubTableGenerator<42>::v,
    BBDirectionsSubTableGenerator<43>::v,
    BBDirectionsSubTableGenerator<44>::v,
    BBDirectionsSubTableGenerator<45>::v,
    BBDirectionsSubTableGenerator<46>::v,
    BBDirectionsSubTableGenerator<47>::v,

    BBDirectionsSubTableGenerator<48>::v,
    BBDirectionsSubTableGenerator<49>::v,
    BBDirectionsSubTableGenerator<50>::v,
    BBDirectionsSubTableGenerator<51>::v,
    BBDirectionsSubTableGenerator<52>::v,
    BBDirectionsSubTableGenerator<53>::v,
    BBDirectionsSubTableGenerator<54>::v,
    BBDirectionsSubTableGenerator<55>::v,

    BBDirectionsSubTableGenerator<56>::v,
    BBDirectionsSubTableGenerator<57>::v,
    BBDirectionsSubTableGenerator<58>::v,
    BBDirectionsSubTableGenerator<59>::v,
    BBDirectionsSubTableGenerator<60>::v,
    BBDirectionsSubTableGenerator<61>::v,
    BBDirectionsSubTableGenerator<62>::v,
    BBDirectionsSubTableGenerator<63>::v,
};


const Direction Geometry::dir(const Square from, const Square to) {
    //int idx = (int)from * 64 + (int)to;
    return directionsTable[(int)from][(int)to];
}


#pragma mark - squares between 2 squares if they are on the same line

#include "Generators/RangesGenerator.hpp"

constexpr std::array<BitBoard, 64 * 64> rangesTable = BBRangeTableGenerator<>::table;

const BitBoard Geometry::range(const Square from, const Square to) {
    int idx = (int)from * 64 + (int)to;
    return rangesTable[idx];
}

#pragma mark - knight

#include "Generators/KnightMoveGenerator.hpp"

constexpr std::array<BitBoard, 64> knightMovesTable = BBKnightMovesTableGenerator<>::table;

const BitBoard Geometry::knightDistances(const Square square) {
    return knightMovesTable[(int)square];
}

#pragma mark - pawn control

#include "Generators/PawnCaptureGenerator.hpp"

constexpr std::array<BitBoard, 128> pawnCapturesTable = BBPawnCapturesTableGenerator<>::table;

const BitBoard Geometry::pawnCaptures(const Square square, const Color color) {
    return pawnCapturesTable[(int)square * 2 + color];
}

#pragma mark - pawn move

#include "Generators/PawnMoveGenerator.hpp"

constexpr std::array<BitBoard, 128> pawnMovesTable = BBPawnMovesTableGenerator<>::table;

const BitBoard Geometry::pawnMoves(const Square square, const Color color) {
    return pawnMovesTable[(int)square * 2 + color];
}

#pragma mark - castle ranges

const BitBoard Geometry::ooFreeRange(const Color color) {
    if(color == White) {
        return range(Square::E1, Square::H1);
    } else {
        return range(Square::E8, Square::H8);
    }
}

const BitBoard Geometry::oooFreeRange(const Color color) {
    if(color == White) {
        return range(Square::E1, Square::A1);
    } else {
        return range(Square::E8, Square::A8);
    }
}

const BitBoard Geometry::ooUncontrolledRange(const Color color) {
    if(color == White) {
        return range(Square::E1, Square::H1);
    } else {
        return range(Square::E8, Square::H8);
    }
}

const BitBoard Geometry::oooUncontrolledRange(const Color color) {
    if(color == White) {
        return range(Square::E1, Square::B1) | bitboard(Square::E1);
    } else {
        return range(Square::E8, Square::B8)  | bitboard(Square::E8);
    }
}

#pragma mark - hits

const Square Geometry::firstByDir(const Square square, Direction dir, const BitBoard mask) {
    BitBoard lineValue = lineTable[(int)square * 8 + dir];
    lineValue = lineValue & mask;
    
    if (!lineValue) return Square::None;
    
    switch(dir) {
        case Direction::NorthWest:
        case Direction::North:
        case Direction::NorthEast:
        case Direction::East:
            // least significant bit
            return Square(ctz64(lineValue));
            break;
        default:
            // most significant bit
            return Square(63 - clz64(lineValue));
            break;
    }
}

const BitBoard Geometry::tillFirstByDir(const Square square, Direction dir, const BitBoard mask) {
    Square first = firstByDir(square, dir, mask);
    BitBoard lineValue = lineTable[(int)square * 8 + dir];
    if (first == Square::None) {
        return lineValue;
    }
    
    BitBoard oppositeLine = lineTable[(int)first * 8 + opposite(dir)];
    
    return (lineValue & oppositeLine) | Geometry::bitboard(first);
}

