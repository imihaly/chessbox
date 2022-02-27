//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef Piece_hpp
#define Piece_hpp

#include "Color.hpp"

namespace chessbox {
    
    // Represents a piece with it's type and color.
    struct Piece {
        
        // Available piece types.
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
        
        // A special piece meaning no piece, usualy on a given aquare.
        static Piece NoPiece;
        
        // The color of the piece.
        Color color;
        
        // The type of the piece.
        Piece::Type type;
        
        Piece(Color color, Piece::Type type) : color(color), type(type) {};
        
        bool operator==(const Piece &p) const {
            return p.type == type && p.color == color;
        }
        
        bool operator!=(const Piece &p) const {
            return p.type != type || p.color != color;
        }
        
        static char typeSymbol(Type type);
    };
    
} // namespace chessbox

#endif /* Piece_hpp */

