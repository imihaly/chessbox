//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "Move.hpp"

#include <algorithm>

#include "Square.hpp"
#include "Piece.hpp"

namespace chessbox {
    std::string Move::description() const {
        std::string ret;
        ret += from.notation() + "-" + to.notation();
        if(promotion != Piece::Type::None) {
            ret += Piece::typeSymbol(promotion);
        }
        return ret;
    }
    
    const Step Move::step() const {
        return to - from;
    }
    
    bool Move::operator==(const Move& other) const {
        return from == other.from && to == other.to && promotion == other.promotion;
    }
    
    Moves& Moves::operator+=(Move move) {
        push_back(move);
        return *this;
    }
    
    Moves& Moves::operator+=(Moves moves) {
        insert(end(), moves.begin(), moves.end());
        return *this;
    }
    
    bool Moves::contains(const Move& move) const {
        return std::find(begin(), end(), move) != end();
    }
    
    std::string Moves::description() const {
        std::string ret;
        for(int idx = 0; idx < size(); idx++) {
            ret += at(idx).description() + " ";
        }
        return ret;
    }
    
}  // namespace chessbox
