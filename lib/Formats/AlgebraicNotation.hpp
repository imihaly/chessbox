//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//


#ifndef AlgebraicNotation_hpp
#define AlgebraicNotation_hpp

#include <stdio.h>
#include <string>
#include "Piece.hpp"

namespace chessbox {
    inline bool isPieceSymbol(char c) {
        return c == 'N' || c == 'B' || c == 'R' || c == 'Q' || c == 'K';
    }
    
    inline bool isPromotionTypeSymbol(char c) {
        return c == 'N' || c == 'B' || c == 'R' || c == 'Q';
    }
    
    inline bool isFileSymbol(char c) {
        return c >= 'a' && c <= 'h';
    }
    
    inline bool isRankSymbol(char c) {
        return c >= '1' && c <= '8';
    }
    
    inline bool isCaptureSymbol(char c) {
        return c == 'x';
    }
    
    inline bool isMoveSymbol(char c) {
        return c == '-';
    }
    
    inline bool isCheckSymbol(char c) {
        return c == '+';
    }
    
    inline bool isCheckmateSymbol(char c) {
        return c == '#';
    }
    
    inline bool isEndSymbol(char c) {
        return c == 0;
    }
    
    inline bool isO(char c) {
        return c == 'O';
    }
    
    inline bool isZero(char c) {
        return c == '0';
    }
    
    inline bool isMinus(char c) {
        return c == '-';
    }
    
    inline std::string symbolForPieceType(Piece::Type pieceType) {
        switch(pieceType) {
            case Piece::Type::Rook:
                return "R";
            case Piece::Type::Knight:
                return "N";
            case Piece::Type::Bishop:
                return "B";
            case Piece::Type::Queen:
                return "Q";
            case Piece::Type::King:
                return "K";
            default:
                return "";
        }
    }
    
    inline Piece::Type pieceTypeFromSymbol(char c) {
        switch(c) {
            case 'N' : return Piece::Type::Knight;
            case 'B' : return Piece::Type::Bishop;
            case 'R' : return Piece::Type::Rook;
            case 'Q' : return Piece::Type::Queen;
            case 'K' : return Piece::Type::King;
        }
        return Piece::Type::None;
    }
    
    inline std::string fileName(int col) {
        char c = 'a' + col;
        return std::string(&c, 1);
    }

    inline std::string rankName(int row) {
        char r = '1' + row;
        return std::string(&r, 1);
    }
    
    inline int fileFromSymbol(char c) {
        return c - 'a';
    }
    
    inline int rankFromSymbol(char c) {
        return c - '1';
    }

}

#endif /* AlgebraicNotation_hpp */
