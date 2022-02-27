//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
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
