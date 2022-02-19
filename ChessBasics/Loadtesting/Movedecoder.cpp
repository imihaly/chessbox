//
// Movedecoder.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Movedecoder.hpp"

Piece::Type pieceTypeFromChar(char c) {
    switch(c) {
        case 'p':
        case 'P': return Piece::Type::Pawn;
            
        case 'r':
        case 'R': return Piece::Type::Rook;
            
        case 'n':
        case 'N': return Piece::Type::Knight;
            
        case 'b':
        case 'B': return Piece::Type::Bishop;
            
        case 'q':
        case 'Q': return Piece::Type::Queen;
            
        case 'k':
        case 'K': return Piece::Type::King;
            
        default: return Piece::Type::None;
    }
}


Move decodeMove(std::string move) {
    const char *buff = move.c_str();
    Square from = Square(buff[0] - 'a', buff[1] - '1');
    Square to = Square(buff[2] - 'a', buff[3] - '1');
    Piece::Type promotion = buff[4] ? pieceTypeFromChar(buff[4]): Piece::Type::None;
    
    return Move(from, to, promotion);
}
