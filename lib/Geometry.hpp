//
// Geometry.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Geometry_hpp
#define Geometry_hpp

#include "Direction.hpp"
#include "Color.hpp"
#include "Square.hpp"

namespace chessbox {
    
    using BitBoard = uint64_t;
    
    class Geometry {
    public:
        static constexpr BitBoard allSquares = -1;
        
    public:
        static const BitBoard bitboard(const Square square);
        static const BitBoard rank(int rankIdx);
        static const BitBoard file(int fileIdx);
        static const BitBoard adjacent(const Square square, Direction dir);
        static const BitBoard adjacents(const Square square);
        static const BitBoard line(const Square square, Direction dir);
        static const BitBoard lines(const Square square);
        static const Direction dir(const Square from, const Square to);
        static const BitBoard range(const Square from, const Square to);
        
        static const BitBoard rookLines(const Square square);
        static const BitBoard bishopLines(const Square square);
        static const BitBoard knightDistances(const Square square);
        static const BitBoard pawnCaptures(const Square square, const Color color);
        static const BitBoard pawnMoves(const Square square, const Color color);
        static const BitBoard ooFreeRange(const Color color);
        static const BitBoard oooFreeRange(const Color color);
        static const BitBoard ooUncontrolledRange(const Color color);
        static const BitBoard oooUncontrolledRange(const Color color);
        
        static const Square firstByDir(const Square square, Direction dir, const BitBoard mask = Geometry::allSquares);
        static const BitBoard tillFirstByDir(const Square square, Direction dir, const BitBoard mask = Geometry::allSquares);
    };
}

#endif /* Geometry_hpp */

