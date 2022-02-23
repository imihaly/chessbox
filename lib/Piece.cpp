//
// Piece.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "Piece.hpp"

namespace chessbox {
    
    Piece Piece::NoPiece = {Color::White, Piece::Type::None};
    
    char Piece::typeName(Type type) {
        static const char pieceNames[] = {
            '.',
            'P',
            'R',
            'N',
            'B',
            'Q',
            'K'
        };
        return pieceNames[type];
    }
    
    char Piece::typeName() const {
        return Piece::typeName(type);
    }
    
    std::string Piece::description() const {
        char pieceName = typeName();
        
        if(color == Color::Black) {
            static int shift = 'A' - 'a';
            pieceName -= shift;
        }
        return std::string(&pieceName, 1);
    }
    
}  // namespace chessbox
