//
// UnitTesting.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "UnitTesting.hpp"
#include "FEN.hpp"

TAU_NO_MAIN()

Position * UnitTesting::positionFromString(const char *string) {
    Position *position = new Position();
    
    for(int c = 0; c < 8; c++) {
        for(int r = 0; r < 8; r++) {
            int idx = (7 - r) * 8 + c;
            Piece::Type type = Piece::Type::None;
            Color color = Color::White;
            switch(string[idx]) {
                case 'p':
                    type = Piece::Type::Pawn;
                    color = Color::Black;
                    break;
                case 'r':
                    type = Piece::Type::Rook;
                    color = Color::Black;
                    break;
                case 'n':
                    type = Piece::Type::Knight;
                    color = Color::Black;
                    break;
                case 'b':
                    type = Piece::Type::Bishop;
                    color = Color::Black;
                    break;
                case 'q':
                    type = Piece::Type::Queen;
                    color = Color::Black;
                    break;
                case 'k':
                    type = Piece::Type::King;
                    color = Color::Black;
                    break;
                case 'P':
                    type = Piece::Type::Pawn;
                    color = Color::White;
                    break;
                case 'R':
                    type = Piece::Type::Rook;
                    color = Color::White;
                    break;
                case 'N':
                    type = Piece::Type::Knight;
                    color = Color::White;
                    break;
                case 'B':
                    type = Piece::Type::Bishop;
                    color = Color::White;
                    break;
                case 'Q':
                    type = Piece::Type::Queen;
                    color = Color::White;
                    break;
                case 'K':
                    type = Piece::Type::King;
                    color = Color::White;
                    break;
            }
            
            if (type != Piece::Type::None) {
                position->setPiece(Piece(color, type), Square(c, r));
            }
        }
    }

    return position;
}

Squares UnitTesting::squaresFromString(const char *string) {
    Squares squares = 0;
    for(int c = 0; c < 8; c++) {
        for(int r = 0; r < 8; r++) {
            int idx = (7 - r) * 8 + c;
            if(string[idx] == 'x') {
                squares.add(Square(c, r));
            }
        }
    }
    return squares;
}

Squares UnitTesting::squaresFromFEN(std::string FEN) {
    Position *position = FEN::positionFromFEN(FEN);
    Squares squares = position->squaresOccupied();
    delete position;
    return squares;
}

bool UnitTesting::isEqual(Moves& op1, Moves& op2) {
    if (op1.size() != op2.size()) return false;
    for(Move m: op1) {
        if(!op2.contains(m)) return false;
    }
    return true;
}

// TODO: idle, transform
std::string longDescription(const Square& square) {
    static const char * columnNames = "ABCDEFGH";
    static char buff[2];
    buff[0] = columnNames[square.col()];
    buff[1] = '1' + square.row();
    return "Square::" + std::string(buff, 2);
}

std::string longDescription(const Squares& squares, const Square& to) {
    std::string ret;
    for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
        ret += "Move(" +  longDescription(*it) + ", " + longDescription(to) + "), ";
    }
    return ret;
}

std::string FENfromSquares(const Squares& squares) {
    Position position;
    for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
        position.setPiece(Piece(Color::White, Piece::Type::Pawn), *it);
    }
    
    return FEN::FENFromPosition(&position, true);
}


