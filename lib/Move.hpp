//
// Move.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Move_hpp
#define Move_hpp

#include "deps.h"
#include "Square.hpp"
#include "Piece.hpp"
#include "Step.hpp"

namespace chessbox {
    
    struct Move {
        Square from;
        Square to;
        Piece::Type promotion;
        
        Move(const Square from = Square::None, const Square to = Square::None, Piece::Type promotion = Piece::Type::None) : from(from), to(to), promotion(promotion) {}
        const Step step() const;
        
        bool operator==(const Move& other) const;
        
        std::string description() const;
    };
    
    std::ostream& operator<<(std::ostream& os, const Move& move);
    
    class Moves: public std::vector<Move> {
    public:
        Moves();
        Moves& operator+=(Move move);
        Moves& operator+=(Moves moves);
        bool contains(const Move& move) const;
        
        std::string description() const;
    };
    
} // namespace chessbox

std::ostream& operator<<(std::ostream& os, const chessbox::Moves& moves);


#endif /* Move_hpp */

