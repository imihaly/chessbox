//
// Movecheck.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Movecheck_hpp
#define Movecheck_hpp

#include "Position.hpp"

namespace chessbox {
    
    // Collection of functions dealing with move validation.
    class Movecheck {
        
        friend class Movegen;
        
    public:
        // Checks if the given move is valid in the given position
        // Performs all required checks including check-detection in the resulting position.
        static bool isValidMove(const Position *position, const Move& move);
        
        // Detects that the moving side's king wouldn't be in check after making this move.
        // Returns true if moving side would be checked after the move.
        // In this function the move can be anything, not needs to be valid by chess rules, it means only a piece relocation.
        static bool detectChecks(const Position *position, const Move& move);
        
    protected:
        // Prechecks the move.
        // Does not evaluate that the move is legal by chess rules, only makes some trivial checks:
        //  - the move is really a move so move.from != move.to
        //  - the landing square is empty or there is a capturable piece on it.
        //  - there is a piece of the moving side on the move.from square.
        static bool precheckMove(const Position *position, const Move& move);
        
        // Checks if the given move looks like a valid pawn move (based on the piece's movement by the game's rules)
        // it doesn't checks:
        //  - what precheck does
        //  - if there is a piece of the required type on the move's from square
        static bool isValidPawnMove(const Position *position, const Move& move);
        
        // Checks if the given move looks like a valid pawn move (based on the piece's movement by the game's rules)
        // it doesn't checks:
        //  - what precheck does
        //  - if there is a piece of the required type on the move's from square
        static bool isValidRookMove(const Position *position, const Move& move);
        
        // Checks if the given move looks like a valid pawn move (based on the piece's movement by the game's rules)
        // it doesn't checks:
        //  - what precheck does
        //  - if there is a piece of the required type on the move's from square
        static bool isValidKnightMove(const Position *position, const Move& move);
        
        // Checks if the given move looks like a valid pawn move (based on the piece's movement by the game's rules)
        // it doesn't checks:
        //  - what precheck does
        //  - if there is a piece of the required type on the move's from square
        static bool isValidBishopMove(const Position *position, const Move& move);
        
        // Checks if the given move looks like a valid pawn move (based on the piece's movement by the game's rules)
        // it doesn't checks:
        //  - what precheck does
        //  - if there is a piece of the required type on the move's from square
        static bool isValidQueenMove(const Position *position, const Move& move);
        
        // Checks if the given move looks like a valid pawn move (based on the piece's movement by the game's rules)
        // it doesn't checks:
        //  - what precheck does
        //  - if there is a piece of the required type on the move's from square
        static bool isValidKingMove(const Position *position, const Move& move);
        
        // Returns if a pawn reaching his goal rank can promote to the given type.
        static bool isValidPromotionType(Piece::Type type);
        
        // Returns wether the given type is capturable by teh game's rules.
        static bool isCapturableType(Piece::Type type);
        
    };
    
} // namespace chessbox

#endif /* Movecheck_hpp */

