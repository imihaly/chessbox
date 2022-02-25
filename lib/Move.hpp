//
// Move.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Move_hpp
#define Move_hpp

#include <vector>

#include "Square.hpp"
#include "Piece.hpp"
#include "Step.hpp"

namespace chessbox {
    
    // represents a chess move.
    struct Move {
        Square from;
        Square to;
        Piece::Type promotion;
        
        Move(const Square from = Square::None, const Square to = Square::None, Piece::Type promotion = Piece::Type::None) : from(from), to(to), promotion(promotion) {}
        
        // Returns the step represented by the move.
        const Step step() const;
        
        // Checks for move equality.
        bool operator==(const Move& other) const;
        
        std::string description() const;
    };
        
    // Collection of moves.
    class Moves: public std::vector<Move> {
    public:
        Moves() = default;
        Moves( std::initializer_list<Move> init ) : std::vector<Move>(init) {}

    public:
        Moves& operator+=(Move move);
        Moves& operator+=(Moves moves);
        bool contains(const Move& move) const;
        
        std::string description() const;
    };
    
} // namespace chessbox

#endif /* Move_hpp */

