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
    
    char Piece::typeSymbol(Type type) {
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
    
}  // namespace chessbox
