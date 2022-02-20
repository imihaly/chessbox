//
// Move.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "Move.hpp"
#include "Square.hpp"
#include "Piece.hpp"

namespace chessbox {
    std::string Move::description() const {
        std::string ret;
        ret += from.description() + "-" + to.description();
        if(promotion != Piece::Type::None) {
            ret += Piece::typeName(promotion);
        }
        return ret;
    }
    
    const Step Move::step() const {
        return to - from;
    }
    
    bool Move::operator==(const Move& other) const {
        return from == other.from && to == other.to && promotion == other.promotion;
    }
    
    std::ostream& operator<<(std::ostream& os, const Move& move) {
        os << move.description();
        return os;
    }
    
    Moves::Moves(): std::vector<Move>() {
        // reserve(20); strangely it slows down
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
    
    std::ostream& operator<<(std::ostream& os, const Moves& moves) {
        os << moves.description();
        return os;
    }
}
