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
    public:
        static Squares squaresControlled(const Position *position, Color side);
        static Squares squaresControlled(const Position *position, const Square square);
        static Squares squaresControlled(const Position *position, const Squares& squares);
        
        static Squares squaresControlling(const Square square, const Position *position, Color side);
        static Squares squaresControlling(const Square square, const Position *position);
        static Squares squaresControlling(const Squares& squares, const Position *position, Color side);
        static Squares squaresControlling(const Squares& squares, const Position *position);
        
        static Squares rooksControlling(const Square square, const Position *position, Color side);
        static Squares bishopsControlling(const Square square, const Position *position, Color side);
        static Squares queensControlling(const Square square, const Position *position, Color side);
        static Squares knightsControlling(const Square square, const Position *position, Color side);
        static Squares pawnsControlling(const Square square, const Position *position, Color side);
        static Squares kingsControlling(const Square square, const Position *position, Color side);
        
        
        static bool isControlling(const Squares& squares, const Position *position, Color side, const Squares& piecesRemoved = 0, const Squares& piecesAdded = 0);
        static bool isControlling(const Square square, const Position *position, Color side, const Squares& piecesRemoved = 0, const Squares& piecesAdded = 0);
        
        static bool isControllingByRookOrQueen(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByBishopOrQueen(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByKnight(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByPawn(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        static bool isControllingByKing(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask = Geometry::allSquares);
        
    };
}

#endif /* Control_hpp */
