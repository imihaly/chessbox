//
// Movegen.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Movegen_hpp
#define Movegen_hpp

#include "Position.hpp"
#include "Move.hpp"

namespace chessbox {
    
    // Collection of functions dealing with move generation.
    class Movegen {
        
    public:
        // Generates the collection of all valid moves from teh given square.
        static const Moves allMovesFrom(Position *position, const Square from);
        
        // Generates the collection of all valid landing on the given square.
        static const Moves allMovesTo(Position *position, const Square to);
        
        // Adds all possible moves from the square `from` to the existing moves collection `result`.
        static const void allMovesFrom(Position *position, const Square from, Moves& result);

        // Adds all possible moves landing on the square `to` to the existing moves collection `result`.
        static const void allMovesTo(Position *position, const Square to, Moves& result);
        
        // Returns the collection of all legal moves in the given position.
        static const Moves allMoves(Position *position);

        // Appends all legal moves in the given position to teh given collection `result`.
        static const void allMoves(Position *position, Moves& result);

    private:
        // Helper methods handling all piece type's moves from a given square.
        static const void allPawnMovesFrom(Position *position, const Square from, Moves& result);
        static const void allRookMovesFrom(Position *position, const Square from, Moves& result);
        static const void allKnightMovesFrom(Position *position, const Square from, Moves& result);
        static const void allBishopMovesFrom(Position *position, const Square from, Moves& result);
        static const void allQueenMovesFrom(Position *position, const Square from, Moves& result);
        static const void allKingMovesFrom(Position *position, const Square from, Moves& result);
        static const void movesToControlledSquares(Position *position, const Square from, Moves& result);
        static const void movesToSquares(Position *position, const Square from, const Squares& squaresTo, Moves& result);
                
        // Helper methods handling all piece type's moves to a given square.
        static const void allPawnMovesTo(Position *position, const Square to, Moves& result);
        static const void allRookMovesTo(Position *position, const Square to, Moves& result);
        static const void allKnightMovesTo(Position *position, const Square to, Moves& result);
        static const void allBishopMovesTo(Position *position, const Square to, Moves& result);
        static const void allQueenMovesTo(Position *position, const Square to, Moves& result);
        static const void allKingMovesTo(Position *position, const Square to, Moves& result);
        
        // Helper method handling long-range pieces moving to a given square.
        static const void allLineMovesTo(Position *position, const Square to, Piece::Type type, Moves& result);
        
        
    };
    
} // namespace chessbox

#endif /* Movegen_hpp */

