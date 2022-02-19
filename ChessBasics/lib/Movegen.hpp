//
// Movegen.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Movegen_hpp
#define Movegen_hpp

#include "deps.h"
#include "Position.hpp"
#include "Move.hpp"

namespace chessbox {
    
    class Movegen {
        
    public:
        static const Moves allMovesFrom(Position *position, const Square from);
        static const Moves allMovesTo(Position *position, const Square to);
        static const void allMovesFrom(Position *position, const Square from, Moves& result);
        static const void allMovesTo(Position *position, const Square to, Moves& result);
        
        // deriverables
        static const Moves allMoves(Position *position);
        static const void allMoves(Position *position, Moves& result);
        
        // helpers
        static const void allPawnMovesFrom(Position *position, const Square from, Moves& result);
        static const void allRookMovesFrom(Position *position, const Square from, Moves& result);
        static const void allKnightMovesFrom(Position *position, const Square from, Moves& result);
        static const void allBishopMovesFrom(Position *position, const Square from, Moves& result);
        static const void allQueenMovesFrom(Position *position, const Square from, Moves& result);
        static const void allKingMovesFrom(Position *position, const Square from, Moves& result);
        static const void movesToControlledSquares(Position *position, const Square from, Moves& result);
        static const void movesToSquares(Position *position, const Square from, const Squares& squaresTo, Moves& result);
        
        
        static const void allPawnMovesTo(Position *position, const Square to, Moves& result);
        static const void allRookMovesTo(Position *position, const Square to, Moves& result);
        static const void allKnightMovesTo(Position *position, const Square to, Moves& result);
        static const void allBishopMovesTo(Position *position, const Square to, Moves& result);
        static const void allQueenMovesTo(Position *position, const Square to, Moves& result);
        static const void allKingMovesTo(Position *position, const Square to, Moves& result);
        
        static const void allLineMovesTo(Position *position, const Square to, Piece::Type type, Moves& result);
        
        
    };
    
}
#endif /* Movegen_hpp */

