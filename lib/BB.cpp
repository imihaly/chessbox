//
// BB.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "BB.hpp"

#include <array>

#include "bitscan.hpp"
#include "Generators/SquareGenerator.hpp"
#include "Generators/RankGenerator.hpp"
#include "Generators/FileGenerator.hpp"
#include "Generators/AdjacentsGenerator.hpp"
#include "Generators/LineGenerator.hpp"
#include "Generators/DirectionsGenerator.hpp"
#include "Generators/RangeGenerator.hpp"
#include "Generators/KnightMoveGenerator.hpp"
#include "Generators/PawnCaptureGenerator.hpp"
#include "Generators/PawnMoveGenerator.hpp"

namespace chessbox {
    
// MARK: - square
    
    constexpr std::array<BitBoard, 64> squaresTable = BBSquaresTableGenerator<>::table;
    
    const BitBoard BB::bitboard(const Square square) {
        return squaresTable[(int)square];
    }
    
// MARK: - rank
        
    static constexpr BitBoard ranksTable[] = {
        BBRankGenerator<0>::v, BBRankGenerator<1>::v, BBRankGenerator<2>::v, BBRankGenerator<3>::v, BBRankGenerator<4>::v, BBRankGenerator<5>::v, BBRankGenerator<6>::v, BBRankGenerator<7>::v
    };
    
    const BitBoard BB::rank(int rankIdx) {
        return ranksTable[rankIdx];
    }
    
// MARK: - file
    
    
    static const BitBoard filesTable[] = {
        BBFileGenerator<0>::v, BBFileGenerator<1>::v, BBFileGenerator<2>::v, BBFileGenerator<3>::v, BBFileGenerator<4>::v, BBFileGenerator<5>::v, BBFileGenerator<6>::v, BBFileGenerator<7>::v
    };
    
    const BitBoard BB::file(int fileIdx) {
        return filesTable[fileIdx];
    }
    
// MARK: - adjacent
        
    constexpr std::array<BitBoard, 512> adjacentsPerDirectionTable = BBAdjacentsPerDirectionTableGenerator<>::table;
    
    const BitBoard BB::adjacent(const Square square, Direction dir) {
        return adjacentsPerDirectionTable[(int)square * 8 + dir];
    }
    
    constexpr std::array<BitBoard, 64> adjacentsTable = BBAdjacentsTableGenerator<>::table;
    
    const BitBoard BB::adjacents(const Square square) {
        return adjacentsTable[(int)square];
    }
    
// MARK: - lines
        
    constexpr std::array<BitBoard, 512> lineTable = BBLinesTableGenerator<>::table;
    constexpr std::array<BitBoard, 64> rookLineTable = BBRookLinesTableGenerator<>::table;
    constexpr std::array<BitBoard, 64> bishopLinesTable = BBBishopLinesTableGenerator<>::table;
    
    const BitBoard BB::line(const Square square, Direction dir) {
        return lineTable[(int)square * 8 + dir];
    }
    
    const BitBoard BB::lines(const Square square) {
        return lineTable[(int)square * 8 + Direction::North] |
        lineTable[(int)square * 8 + Direction::NorthEast] |
        lineTable[(int)square * 8 + Direction::East] |
        lineTable[(int)square * 8 + Direction::SouthEast] |
        lineTable[(int)square * 8 + Direction::South] |
        lineTable[(int)square * 8 + Direction::SouthWest] |
        lineTable[(int)square * 8 + Direction::West] |
        lineTable[(int)square * 8 + Direction::NorthWest];
    }
    
    const BitBoard BB::rookLines(const Square square) {
        return rookLineTable[(int)square];
    }
    
    const BitBoard BB::bishopLines(const Square square) {
        return bishopLinesTable[(int)square];
    }
    
// MARK: - directions defined by 2 squares
        
    constexpr std::array<std::array<Direction, 64>, 64> directionsTable = {
        BBDirectionTableGenerator<0>::v,
        BBDirectionTableGenerator<1>::v,
        BBDirectionTableGenerator<2>::v,
        BBDirectionTableGenerator<3>::v,
        BBDirectionTableGenerator<4>::v,
        BBDirectionTableGenerator<5>::v,
        BBDirectionTableGenerator<6>::v,
        BBDirectionTableGenerator<7>::v,
        
        BBDirectionTableGenerator<8>::v,
        BBDirectionTableGenerator<9>::v,
        BBDirectionTableGenerator<10>::v,
        BBDirectionTableGenerator<11>::v,
        BBDirectionTableGenerator<12>::v,
        BBDirectionTableGenerator<13>::v,
        BBDirectionTableGenerator<14>::v,
        BBDirectionTableGenerator<15>::v,
        
        BBDirectionTableGenerator<16>::v,
        BBDirectionTableGenerator<17>::v,
        BBDirectionTableGenerator<18>::v,
        BBDirectionTableGenerator<19>::v,
        BBDirectionTableGenerator<20>::v,
        BBDirectionTableGenerator<21>::v,
        BBDirectionTableGenerator<22>::v,
        BBDirectionTableGenerator<23>::v,
        
        BBDirectionTableGenerator<24>::v,
        BBDirectionTableGenerator<25>::v,
        BBDirectionTableGenerator<26>::v,
        BBDirectionTableGenerator<27>::v,
        BBDirectionTableGenerator<28>::v,
        BBDirectionTableGenerator<29>::v,
        BBDirectionTableGenerator<30>::v,
        BBDirectionTableGenerator<31>::v,
        
        BBDirectionTableGenerator<32>::v,
        BBDirectionTableGenerator<33>::v,
        BBDirectionTableGenerator<34>::v,
        BBDirectionTableGenerator<35>::v,
        BBDirectionTableGenerator<36>::v,
        BBDirectionTableGenerator<37>::v,
        BBDirectionTableGenerator<38>::v,
        BBDirectionTableGenerator<39>::v,
        
        BBDirectionTableGenerator<40>::v,
        BBDirectionTableGenerator<41>::v,
        BBDirectionTableGenerator<42>::v,
        BBDirectionTableGenerator<43>::v,
        BBDirectionTableGenerator<44>::v,
        BBDirectionTableGenerator<45>::v,
        BBDirectionTableGenerator<46>::v,
        BBDirectionTableGenerator<47>::v,
        
        BBDirectionTableGenerator<48>::v,
        BBDirectionTableGenerator<49>::v,
        BBDirectionTableGenerator<50>::v,
        BBDirectionTableGenerator<51>::v,
        BBDirectionTableGenerator<52>::v,
        BBDirectionTableGenerator<53>::v,
        BBDirectionTableGenerator<54>::v,
        BBDirectionTableGenerator<55>::v,
        
        BBDirectionTableGenerator<56>::v,
        BBDirectionTableGenerator<57>::v,
        BBDirectionTableGenerator<58>::v,
        BBDirectionTableGenerator<59>::v,
        BBDirectionTableGenerator<60>::v,
        BBDirectionTableGenerator<61>::v,
        BBDirectionTableGenerator<62>::v,
        BBDirectionTableGenerator<63>::v,
    };
    
    
    const Direction BB::dir(const Square from, const Square to) {
        return directionsTable[(int)from][(int)to];
    }
    
    
// MARK: - squares between 2 squares if they are on the same line
        
    constexpr std::array<std::array<BitBoard, 64>, 64> rangesTable = {
        BBRangeTableGenerator<0>::v,
        BBRangeTableGenerator<1>::v,
        BBRangeTableGenerator<2>::v,
        BBRangeTableGenerator<3>::v,
        BBRangeTableGenerator<4>::v,
        BBRangeTableGenerator<5>::v,
        BBRangeTableGenerator<6>::v,
        BBRangeTableGenerator<7>::v,
        
        BBRangeTableGenerator<8>::v,
        BBRangeTableGenerator<9>::v,
        BBRangeTableGenerator<10>::v,
        BBRangeTableGenerator<11>::v,
        BBRangeTableGenerator<12>::v,
        BBRangeTableGenerator<13>::v,
        BBRangeTableGenerator<14>::v,
        BBRangeTableGenerator<15>::v,
        
        BBRangeTableGenerator<16>::v,
        BBRangeTableGenerator<17>::v,
        BBRangeTableGenerator<18>::v,
        BBRangeTableGenerator<19>::v,
        BBRangeTableGenerator<20>::v,
        BBRangeTableGenerator<21>::v,
        BBRangeTableGenerator<22>::v,
        BBRangeTableGenerator<23>::v,
        
        BBRangeTableGenerator<24>::v,
        BBRangeTableGenerator<25>::v,
        BBRangeTableGenerator<26>::v,
        BBRangeTableGenerator<27>::v,
        BBRangeTableGenerator<28>::v,
        BBRangeTableGenerator<29>::v,
        BBRangeTableGenerator<30>::v,
        BBRangeTableGenerator<31>::v,
        
        BBRangeTableGenerator<32>::v,
        BBRangeTableGenerator<33>::v,
        BBRangeTableGenerator<34>::v,
        BBRangeTableGenerator<35>::v,
        BBRangeTableGenerator<36>::v,
        BBRangeTableGenerator<37>::v,
        BBRangeTableGenerator<38>::v,
        BBRangeTableGenerator<39>::v,
        
        BBRangeTableGenerator<40>::v,
        BBRangeTableGenerator<41>::v,
        BBRangeTableGenerator<42>::v,
        BBRangeTableGenerator<43>::v,
        BBRangeTableGenerator<44>::v,
        BBRangeTableGenerator<45>::v,
        BBRangeTableGenerator<46>::v,
        BBRangeTableGenerator<47>::v,
        
        BBRangeTableGenerator<48>::v,
        BBRangeTableGenerator<49>::v,
        BBRangeTableGenerator<50>::v,
        BBRangeTableGenerator<51>::v,
        BBRangeTableGenerator<52>::v,
        BBRangeTableGenerator<53>::v,
        BBRangeTableGenerator<54>::v,
        BBRangeTableGenerator<55>::v,
        
        BBRangeTableGenerator<56>::v,
        BBRangeTableGenerator<57>::v,
        BBRangeTableGenerator<58>::v,
        BBRangeTableGenerator<59>::v,
        BBRangeTableGenerator<60>::v,
        BBRangeTableGenerator<61>::v,
        BBRangeTableGenerator<62>::v,
        BBRangeTableGenerator<63>::v,
    };
    
    
    const BitBoard BB::range(const Square from, const Square to) {
        return rangesTable[(int)from][(int)to];
    }
    
// MARK: - knight
        
    constexpr std::array<BitBoard, 64> knightMovesTable = BBKnightMovesTableGenerator<>::table;
    
    const BitBoard BB::knightDistances(const Square square) {
        return knightMovesTable[(int)square];
    }
    
// MARK: - pawn control
        
    constexpr std::array<BitBoard, 128> pawnCapturesTable = BBPawnCapturesTableGenerator<>::table;
    
    const BitBoard BB::pawnCaptures(const Square square, const Color color) {
        return pawnCapturesTable[(int)square * 2 + color];
    }
    
// MARK: - pawn move
        
    constexpr std::array<BitBoard, 128> pawnMovesTable = BBPawnMovesTableGenerator<>::table;
    
    const BitBoard BB::pawnMoves(const Square square, const Color color) {
        return pawnMovesTable[(int)square * 2 + color];
    }
    
// MARK: - castle ranges
    
    const BitBoard BB::ooFreeRange(const Color color) {
        if(color == White) {
            return range(Square::E1, Square::H1);
        } else {
            return range(Square::E8, Square::H8);
        }
    }
    
    const BitBoard BB::oooFreeRange(const Color color) {
        if(color == White) {
            return range(Square::E1, Square::A1);
        } else {
            return range(Square::E8, Square::A8);
        }
    }
    
    const BitBoard BB::ooUncontrolledRange(const Color color) {
        if(color == White) {
            return range(Square::E1, Square::H1);
        } else {
            return range(Square::E8, Square::H8);
        }
    }
    
    const BitBoard BB::oooUncontrolledRange(const Color color) {
        if(color == White) {
            return range(Square::E1, Square::B1) | bitboard(Square::E1);
        } else {
            return range(Square::E8, Square::B8)  | bitboard(Square::E8);
        }
    }
    
// MARK: - hits
    
    const Square BB::firstByDir(const Square square, Direction dir, const BitBoard mask) {
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
    
    const BitBoard BB::tillFirstByDir(const Square square, Direction dir, const BitBoard mask) {
        Square first = firstByDir(square, dir, mask);
        BitBoard lineValue = lineTable[(int)square * 8 + dir];
        if (first == Square::None) {
            return lineValue;
        }
        
        BitBoard oppositeLine = lineTable[(int)first * 8 + opposite(dir)];
        
        return (lineValue & oppositeLine) | BB::bitboard(first);
    }
    
}  // namespace chessbox
