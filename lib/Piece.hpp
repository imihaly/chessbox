//
// Piece.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Piece_hpp
#define Piece_hpp

#include "deps.h"
#include "Color.hpp"


namespace chessbox {
    
    struct Piece {
        enum Type : char{
            None,
            Pawn,
            Rook,
            Knight,
            Bishop,
            Queen,
            King,
            Count
        };
        
        
        static Piece NoPiece;
        
        Color color;
        Piece::Type type;
        
        Piece(Color color, Piece::Type type) : color(color), type(type) {};
        
        bool operator==(const Piece &p) const {
            return p.type == type && p.color == color;
        }
        
        bool operator!=(const Piece &p) const {
            return p.type != type || p.color != color;
        }
        
        static char typeName(Type type);
        char typeName() const;
        std::string description() const;
    };
    
} // namespace chessbox

std::ostream& operator<<(std::ostream& os, const chessbox::Piece& piece);

#endif /* Piece_hpp */

