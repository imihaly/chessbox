//
// FEN.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "FEN.hpp"

char charFromPiece(Piece piece);
Piece pieceFromChar(char c);
bool parsePiecesField(const char*& buff, Position *position);
bool parseMoveField(const char*& buff, Position *position);
bool parseCastleField(const char*& buff, Position *position);
bool parseEnPassantField(const char*& buff, Position *position);
bool parseHalfMoveField(const char*& buff, Position *position);
bool parseMoveIndexField(const char*& buff, Position *position);
Square parseSquare(const char*& buff);

Position * FEN::positionFromFEN(std::string FEN, const char **parseErrorAt) {
    Position *position = new Position();
    const char *buff = FEN.c_str();

    if(parsePiecesField(buff, position) &&
       parseMoveField(buff, position) &&
       parseCastleField(buff, position) &&
       parseEnPassantField(buff, position) &&
       parseHalfMoveField(buff, position) &&
       parseMoveIndexField(buff, position)) {
        return position;
    }
                        
    delete position;
    if (parseErrorAt) {
        *parseErrorAt = buff;
    }
    return NULL;
}

bool parsePiecesField(const char*& buff, Position *position) {
    int row = 7;
    int col = 0;
    while(*buff) {
        if (*buff == '/') {
            if (col != 8) {
                return false;
            }
            row--;
            col = 0;
            buff++;
            continue;
        }
        
        if (*buff == ' ') {
            // end of pieces
            // validate if all board is filled
            if (row > 0) {
                return false;
            }
            if (col != 8) {
                return false;
            }

            buff++;
            return true;
        }

        if(isnumber(*buff)) {
            col += atoi(buff);
            if (col > 8) {
                return false;
            }
        } else {
            Piece piece = pieceFromChar(*buff);
            
            // check if piece can be parsed out
            if (piece == Piece::NoPiece) {
                return false;
            }
            
            if (col >= 8) {
                buff--;
                return false;
            }
            if (row < 0) {
                buff--;
                return false;
            }

            position->setPiece(piece, Square(col, row));
            col++;
        }

        buff++;
    }
    
    return true;
}

bool parseMoveField(const char*& buff, Position *position) {
    switch(*buff) {
        case 'w':
            position->setSideToMove(Color::White);
            break;
        case 'b':
            position->setSideToMove(Color::Black);
            break;
        default:
            return false;
    }
    buff++;
    if (*buff != ' ') {
        return false;
    }
    
    buff++;
    return true;
}

// [KQkq]+|-
bool parseCastleField(const char*& buff, Position *position) {
    position->setCastleKingside(Color::White, false);
    position->setCastleQueenside(Color::White, false);
    position->setCastleKingside(Color::Black, false);
    position->setCastleQueenside(Color::Black, false);
    
    if (*buff == '-') {
        buff++;
    } else {
        bool finished = false;
        while(*buff && !finished) {
            switch (*buff++) {
                case 'K': position->setCastleKingside(Color::White, true); break;
                case 'k': position->setCastleKingside(Color::Black, true); break;
                case 'Q': position->setCastleQueenside(Color::White, true); break;
                case 'q': position->setCastleQueenside(Color::Black, true); break;
                default:
                    buff--;
                    finished = true;
            }
        }
    }
    
    if (*buff != ' ') {
        return false;
    }
    
    buff++;
    return true;
}

bool parseEnPassantField(const char*& buff, Position *position) {
    if (*buff == '-') {
        position->setEnPassantSquare(Square::None);
        buff++;
    } else {
        Square sq = parseSquare(buff);
        if (sq == Square::None) {
            // parse error
            return false;
        }
        position->setEnPassantSquare(sq);
    }
    
    // check for delimiter
    if (*buff != ' ') {
        return false;
    }
    
    buff++;
    return true;
}

Square parseSquare(const char*& buff) {
    int col = -1;
    int row = -1;
    if(*buff >= 'a' && *buff <= 'h') {
        col = *buff - 'a';
        buff++;
    } else {
        return Square::None;
    }

    if(*buff >= '1' && *buff <= '8') {
        row = *buff - '1';
        buff++;
    } else {
        return Square::None;
    }
    
    return Square(col, row);
}

bool parseHalfMoveField(const char*& buff, Position *position) {
    if(!*buff) {
        return false;
    }
    position->setHalfMovesSinceLastPawnMoveOrCapture(atoi(buff));
    while(*buff) {
        if (isnumber(*buff)) {
            buff++;
        } else if (*buff == ' ') {
            buff++;
            return true;
        } else {
            return false;
        }
    }
    return true;
}

bool parseMoveIndexField(const char*& buff, Position *position) {
    if(!*buff) {
        return false;
    }
    position->setMoveIndex(atoi(buff));
    while(*buff) {
        if (isnumber(*buff)) {
            buff++;
        } else if (*buff == ' ') {
            buff++;
            return true;
        } else {
            // parse error
            return false;
        }
    }
    return true;
}

const std::string FEN::FENFromPosition(const Position *position, bool addMoveFields) {
    std::stringstream fen;
    
    // add pieces
    for(int row = 7; row >= 0; row--) {
        if(row != 7) fen << "/";
        
        int emptyCount = 0;
        for(int col = 0; col < 8; col++) {
            const Piece& piece = position->pieceOnSquare(Square(col, row));
            if(piece == Piece::NoPiece) {
                emptyCount++;
            } else {
                if(emptyCount) {
                    fen << emptyCount;
                }
                emptyCount = 0;
                fen << charFromPiece(piece);
            }
        }
        if(emptyCount) {
            fen << emptyCount;
        }
    }
    
    // add moving side
    fen << (position->sideToMove() == Color::White ? " w" : " b");
        
    // add castling field
    bool castlingAvailable =
        position->canCastleKingside(Color::White) ||
        position->canCastleQueenside(Color::White) ||
        position->canCastleKingside(Color::Black) ||
        position->canCastleQueenside(Color::Black);

    if(!castlingAvailable) {
        fen << " -";
    } else {
        fen << " ";
        if(position->canCastleKingside(Color::White)) fen << "K";
        if(position->canCastleQueenside(Color::White)) fen << "Q";
        if(position->canCastleKingside(Color::Black)) fen << "k";
        if(position->canCastleQueenside(Color::Black)) fen << "q";
    }
    
    // add enpasant filed
    if(position->enPassantSquare() == Square::None) {
        fen << " -";
    } else {
        fen << " " << position->enPassantSquare().description();
    }

    if(addMoveFields) {
        // add half move
        fen << " " << position->halfMovesSinceLastPawnMoveOrCapture();
        
        // add move index
        fen << " " << position->moveIndex();
    }
    
    return fen.str();
}

#pragma mark - helpers

char charFromPiece(Piece piece) {
    static const char pieceNames[] = {
        ' ',
        'p',
        'r',
        'n',
        'b',
        'q',
        'k'
    };
    
    char c = pieceNames[piece.type];
    if (piece.color == Color::White) {
        c += 'A' - 'a';
    }
    
    return c;
}

Piece pieceFromChar(char c) {
    switch(c) {
        case 'p': return Piece(Color::Black, Piece::Type::Pawn);
        case 'P': return Piece(Color::White, Piece::Type::Pawn);
            
        case 'r': return Piece(Color::Black, Piece::Type::Rook);
        case 'R': return Piece(Color::White, Piece::Type::Rook);
            
        case 'n': return Piece(Color::Black, Piece::Type::Knight);
        case 'N': return Piece(Color::White, Piece::Type::Knight);
            
        case 'b': return Piece(Color::Black, Piece::Type::Bishop);
        case 'B': return Piece(Color::White, Piece::Type::Bishop);
            
        case 'q': return Piece(Color::Black, Piece::Type::Queen);
        case 'Q': return Piece(Color::White, Piece::Type::Queen);
            
        case 'k': return Piece(Color::Black, Piece::Type::King);
        case 'K': return Piece(Color::White, Piece::Type::King);
            
        default: return Piece::NoPiece;
    }
}

