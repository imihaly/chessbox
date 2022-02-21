//
// BB.hpp
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
    
    class BB {
    public:
        static constexpr BitBoard allSquares = -1;
        
    public:
        
        // returns the bitboard representation of the given square.
        static const BitBoard bitboard(const Square square);
        
        // returns the bitboard representation of the given rank.
        static const BitBoard rank(int rankIdx);
        
        // returns the bitboard representation of the given file.
        static const BitBoard file(int fileIdx);
        
        // returns the bitboard representation of the square adjacent to the given `square` in the given `direction`.
        static const BitBoard adjacent(const Square square, Direction dir);
        
        // returns the bitboard representation of the squares adjacent to the given `square`.
        static const BitBoard adjacents(const Square square);
        
        // returns the bitboard representation of a partial -file, -rank or -diagonal starting near the `square` and running in the given `direction`.
        // example:
        //   if square == e4 and direction is `North` the returned bitboard contains the squares: { e5, e6, e7, e8 }
        static const BitBoard line(const Square square, Direction dir);
        
        // returns the bitboard representation containing all lines starting at `square` and running in any direction.
        // see: `BitBoard line(const Square square, Direction dir)`
        static const BitBoard lines(const Square square);
        
        // returns the direction in which the square `to` id from square `from`.
        // returns `Direction::Any` if to == from
        // returns `Direction::Unknown` if to and from is not on the same file, rank or diagonal.
        static const Direction dir(const Square from, const Square to);
        
        // returns the collection of squares between `from` and `too` if they are on teh same line (file, rank or diagonal).
        // returns Bitboard(0) otherwise.
        // `to` and `from` are not included into the collection.
        static const BitBoard range(const Square from, const Square to);
        
        // returns the collection of rookLines (file or rank) containing the given `square`.
        static const BitBoard rookLines(const Square square);
        
        
        static const BitBoard bishopLines(const Square square);
        static const BitBoard knightDistances(const Square square);
        static const BitBoard pawnCaptures(const Square square, const Color color);
        static const BitBoard pawnMoves(const Square square, const Color color);
        static const BitBoard ooFreeRange(const Color color);
        static const BitBoard oooFreeRange(const Color color);
        static const BitBoard ooUncontrolledRange(const Color color);
        static const BitBoard oooUncontrolledRange(const Color color);
        
        static const Square firstByDir(const Square square, Direction dir, const BitBoard mask = BB::allSquares);
        static const BitBoard tillFirstByDir(const Square square, Direction dir, const BitBoard mask = BB::allSquares);
    };
    
} // namespace chessbox

#endif /* Geometry_hpp */

