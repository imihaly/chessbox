//
// Control.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Control_hpp
#define Control_hpp

#include "Position.hpp"

namespace chessbox {
    
    // Collection of functions dealing with square-control.
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
        static Squares squaresControlling(const Position *position, const Square square, Color side);
        
        // Returns the squares from which the given square is under control by a piece of either side.
        static Squares squaresControlling(const Position *position, const Square square);
        
        // Returns the squares from which any of the given squares is under control by a piece of the given side.
        static Squares squaresControlling(const Position *position, const Squares& squares, Color side);

        // Returns the squares from which any of the given squares is under control by a piece of either side.
        static Squares squaresControlling(const Position *position, const Squares& squares);

        // Returns if there would be any piece of color `side` controlling any of the squares in `squares` considering the changes in `pieces` removed and `piecesAdded`
        static bool isControlling(const Position *position, const Squares& squares, Color side, const Squares& piecesRemoved = 0, const Squares& piecesAdded = 0);
        
        // Returns if there would be any piece of color `side` controlling square considering the changes in `pieces` removed and `piecesAdded`
        static bool isControlling(const Position *position, const Square square, Color side, const Squares& piecesRemoved = 0, const Squares& piecesAdded = 0);
        
    private:
        // Returns the squares from which the given square is controlled by a rook of the given side.
        static Squares rooksControlling(const Position *position, const Square square, Color side);

        // Returns the squares from which the given square is controlled by a bishop of the given side.
        static Squares bishopsControlling(const Position *position, const Square square, Color side);

        // Returns the squares from which the given square is controlled by a queen of the given side.
        static Squares queensControlling(const Position *position, const Square square, Color side);

        // Returns the squares from which the given square is controlled by a knight of the given side.
        static Squares knightsControlling(const Position *position, const Square square, Color side);

        // Returns the squares from which the given square is controlled by a pawn of the given side.
        static Squares pawnsControlling(const Position *position, const Square square, Color side);

        // Returns the square from which the given square is controlled by the king of the given side.
        static Squares kingsControlling(const Position *position, const Square square, Color side);
        
    private:
        // Returns if there would be any rook or queen of color `side` controlling square considering the changes in `pieces` removed and `piecesAdded`
        // Only the pieces on squares in `mask` are checked.
        static bool isControllingByRookOrQueen(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = BB::allSquares);

        // Returns if there would be any bishop or queen of color `side` controlling square considering the changes in `pieces` removed and `piecesAdded`
        // Only the pieces on squares in `mask` are checked.
        static bool isControllingByBishopOrQueen(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = BB::allSquares);

        // Returns if there would be any knoght of color `side` controlling square considering the changes in `pieces` removed and `piecesAdded`
        // Only the pieces on squares in `mask` are checked.
        static bool isControllingByKnight(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = BB::allSquares);

        // Returns if there would be any pawn of color `side` controlling square considering the changes in `pieces` removed and `piecesAdded`
        // Only the pieces on squares in `mask` are checked.
        static bool isControllingByPawn(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = BB::allSquares);

        // Returns if there would be any king of color `side` controlling square considering the changes in `pieces` removed and `piecesAdded`
        // Only the pieces on squares in `mask` are checked.
        static bool isControllingByKing(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = BB::allSquares);
        
    };
    
} // namespace chessbox

#endif /* Control_hpp */
