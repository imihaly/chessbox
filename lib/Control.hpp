//
// Control.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Control_hpp
#define Control_hpp

#include "deps.h"
#include "Position.hpp"

namespace chessbox {
    
    class Control {
        friend class Movecheck;
        
    public:
        // Returns the collection of squares controlled by any of the given side's piece.
        static Squares squaresControlled(const Position *position, Color side);
        
        // Returns the collection of squares controlled by the piece on the given square.
        // If the square is empty, an empty set will be returned.
        static Squares squaresControlled(const Position *position, const Square square);
        
        // Returns the collection of squares controlled by the pieces on the given square.
        static Squares squaresControlled(const Position *position, const Squares& squares);

        // Returns the squares from which the given square is under control by a piece of the given side.
        static Squares squaresControlling(const Square square, const Position *position, Color side);
        
        // Returns the squares from which the given square is under control by a piece of either side.
        static Squares squaresControlling(const Square square, const Position *position);
        
        // Returns the squares from which any of the given squares is under control by a piece of the given side.
        static Squares squaresControlling(const Squares& squares, const Position *position, Color side);

        // Returns the squares from which any of the given squares is under control by a piece of either side.
        static Squares squaresControlling(const Squares& squares, const Position *position);
        
        // Returns the squares from which the given square is controlled by a rook of the given side.
        static Squares rooksControlling(const Square square, const Position *position, Color side);

        // Returns the squares from which the given square is controlled by a bishop of the given side.
        static Squares bishopsControlling(const Square square, const Position *position, Color side);

        // Returns the squares from which the given square is controlled by a queen of the given side.
        static Squares queensControlling(const Square square, const Position *position, Color side);

        // Returns the squares from which the given square is controlled by a knight of the given side.
        static Squares knightsControlling(const Square square, const Position *position, Color side);

        // Returns the squares from which the given square is controlled by a pawn of the given side.
        static Squares pawnsControlling(const Square square, const Position *position, Color side);

        // Returns the square from which the given square is controlled by the king of the given side.
        static Squares kingsControlling(const Square square, const Position *position, Color side);
        
    private:
        static bool isControlling(const Squares& squares, const Position *position, Color side, const Squares& piecesRemoved = 0, const Squares& piecesAdded = 0);
        static bool isControlling(const Square square, const Position *position, Color side, const Squares& piecesRemoved = 0, const Squares& piecesAdded = 0);
        
        static bool isControllingByRookOrQueen(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByBishopOrQueen(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByKnight(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByPawn(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByKing(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        
    };
    
} // namespace chessbox

#endif /* Control_hpp */
