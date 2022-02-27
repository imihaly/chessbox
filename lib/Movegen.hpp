//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
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
        static const Moves allMovesFrom(const Position *position, const Square from);
        
        // Generates the collection of all valid landing on the given square.
        static const Moves allMovesTo(const Position *position, const Square to);
        
        // Adds all possible moves from the square `from` to the existing moves collection `result`.
        static const void allMovesFrom(const Position *position, const Square from, Moves& result);

        // Adds all possible moves landing on the square `to` to the existing moves collection `result`.
        static const void allMovesTo(const Position *position, const Square to, Moves& result);
        
        // Returns the collection of all legal moves in the given position.
        static const Moves allMoves(const Position *position);

        // Appends all legal moves in the given position to teh given collection `result`.
        static const void allMoves(const Position *position, Moves& result);

    private:
        // Helper methods handling all piece type's moves from a given square.
        static const void allPawnMovesFrom(const Position *position, const Square from, Moves& result);
        static const void allRookMovesFrom(const Position *position, const Square from, Moves& result);
        static const void allKnightMovesFrom(const Position *position, const Square from, Moves& result);
        static const void allBishopMovesFrom(const Position *position, const Square from, Moves& result);
        static const void allQueenMovesFrom(const Position *position, const Square from, Moves& result);
        static const void allKingMovesFrom(const Position *position, const Square from, Moves& result);
        static const void movesToControlledSquares(const Position *position, const Square from, Moves& result);
        static const void movesToSquares(const Position *position, const Square from, const Squares& squaresTo, Moves& result);
                
        // Helper methods handling all piece type's moves to a given square.
        static const void allPawnMovesTo(const Position *position, const Square to, Moves& result);
        static const void allRookMovesTo(const Position *position, const Square to, Moves& result);
        static const void allKnightMovesTo(const Position *position, const Square to, Moves& result);
        static const void allBishopMovesTo(const Position *position, const Square to, Moves& result);
        static const void allQueenMovesTo(const Position *position, const Square to, Moves& result);
        static const void allKingMovesTo(const Position *position, const Square to, Moves& result);
        
        // Helper method handling long-range pieces moving to a given square.
        static const void allLineMovesTo(const Position *position, const Square to, Piece::Type type, Moves& result);
        
        
    };
    
} // namespace chessbox

#endif /* Movegen_hpp */

