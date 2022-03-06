//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//



#include "SAN.hpp"
#include <cctype>
#include <string>
#include <sstream>
#include "AlgebraicNotation.hpp"
#include "../Movecheck.hpp"
#include "../Movegen.hpp"

namespace chessbox {
    
    std::string resolveAmbiguityForMove(const Position* position, const Move& move) {
        Moves moves = Movegen::allMovesTo(position, move.to, position->pieceOnSquare(move.from).type);
        if (moves.size() <= 1) return "";
        
        int sameFile = 0;
        int sameRank = 0;
        int samePromotion = 0;

        for(Move m: moves) {
            if(m.promotion == move.promotion) samePromotion++;
            if(m.from.col() == move.from.col()) sameFile++;
            if(m.from.row() == move.from.row()) sameRank++;
        }
        
        if (samePromotion == 1) {
            // promotion will be at the end of notation anyway
            return "";
        }
        
        if (sameFile == 1) {
            return fileName(move.from.col());
        }
        
        if(sameRank == 1) {
            return rankName(move.from.row());
        }
        
        return move.from.notation();
    }
    

    std::string SAN::notationForMove(const Position* position, const Move& move) {
        std::ostringstream os;
        if (!Movecheck::isValidMove(position, move)) {
            return "";
        }
        
        if (Movecheck::isKingsideCastleMove(position, move)) {
            os<<"O-O";
        } else if (Movecheck::isQueensideCastleMove(position, move)) {
            os<<"O-O-O";
        } else {
            bool pawnMove = position->pieceOnSquare(move.from).type == Piece::Type::Pawn;
            bool isCapture = Movecheck::isCaptureMove(position, move);
            
            if(pawnMove && isCapture) {
                os << fileName(move.from.col());
            } else {
                os << symbolForPieceType(position->pieceOnSquare(move.from).type);
                os << resolveAmbiguityForMove(position, move);
            }
            if(isCapture) {
                os << "x";
            }
            os << move.to.notation();
            os << symbolForPieceType(move.promotion);
        }
        
        Position *positionAfterMove = position->positionWithMove(move);
        if(positionAfterMove->isMate()) {
            os<<"#";
        } else if(positionAfterMove->isKingChecked()) {
            os<<"+";
        }
        delete positionAfterMove;
        
        return os.str();
    }
    
    struct SANParsingMachine {
        int state = 0;
        int consumed = 0;
        
        Piece::Type pieceType = Piece::Type::Pawn;
        Piece::Type promotionType = Piece::Type::None;;
        bool isCapture = false;
        bool isCheck = false;
        bool isMate = false;
        bool isShortCastle = false;
        bool isLongCastle = false;
        std::vector<char> coordinates;
        
        const Position *position;
        Move m;
        
        enum State {
#include "Grammar/GrammarDecl.hpp"
#include "Grammar/SANGrammar.hpp"
        };
        
        SANParsingMachine(const Position *position): position(position) {}
        
        bool isFinished() {
            return  state == End;
        }
        
        std::shared_ptr<Error> buildAndValidateMove() {
            if(isShortCastle) {
                if(position->sideToMove() == Color::White) {
                    m = Move(Square::E1, Square::G1);
                } else {
                    m = Move(Square::E8, Square::G8);
                }
                return Movecheck::isValidMove(position, m) ? nullptr : std::make_shared<SemanticError>("Decoded move (" + m.description() + ") is invalid in the given position!");
            }

            if(isLongCastle) {
                if(position->sideToMove() == Color::White) {
                    m = Move(Square::E1, Square::C1);
                } else {
                    m = Move(Square::E8, Square::C8);
                }
                return Movecheck::isValidMove(position, m) ? nullptr : std::make_shared<SemanticError>("Decoded move (" + m.description() + ") is invalid in the given position!");
            }
            
            // last two coordinates are the landing square
            if (coordinates.size() < 2) {
                // I think this will never happend because it will result in a parse error.
                return std::make_shared<SemanticError>("Landing squre is not specified!");;
            }
            
            int toFile = fileFromSymbol(coordinates[coordinates.size() - 2]);
            int toRank = rankFromSymbol(coordinates[coordinates.size() - 1]);
            coordinates.pop_back();
            coordinates.pop_back();

            
            Moves moves = Movegen::allMovesTo(position, Square(toFile, toRank), pieceType);
            if(moves.size() == 0) {
                return std::make_shared<SemanticError>("Could not find any move matching the specified criteria!");;
            }
            
            if(moves.size() == 1) {
                m = moves[0];
                return nullptr;
            }

            // solve disambiguity
            for(Move move: moves) {

                if (move.promotion != promotionType) continue;
                bool matching = true;
                
                for(char c: coordinates) {
                    if(isFileSymbol(c) && move.from.col() != fileFromSymbol(c)) {
                        matching = false;
                        break;
                    }
                    if(isRankSymbol(c) && move.from.row() != rankFromSymbol(c))  {
                        matching = false;
                        break;
                    }
                }
                if(matching) {
                    m = move;
                    return nullptr;
                }
            }

            // semantic error
            return std::make_shared<SemanticError>("Could not find any move matching the specified criteria! Candidates were: " + moves.description());
        }
        
        void setShortCastle() {
            isShortCastle = true;
        }
        
        void setLongCastle() {
            isLongCastle = true;
        }
        
        bool consume(char c) {
            consumed++;
            if (isspace(c)) return true;

            do {
                switch(state) {
#include "Grammar/GrammarDef.hpp"
#include "Grammar/SANGrammar.hpp"
                }
                
            } while(true);
            
            return false;
        }
        
    };
    
    SAN::Result SAN::moveFromNotation(const Position *position, const std::string notation) {
        SANParsingMachine parser(position);
        for(std::string::const_iterator it = notation.cbegin(); it != notation.cend(); ++it) {
            if(!parser.consume(*it)) {
                return SAN::Result(std::make_shared<ParseError>(parser.consumed));
            }
        }
        
        // end of notation
        if(!parser.consume(0)) {
            return SAN::Result(std::make_shared<ParseError>(parser.consumed));
        }
        
        if (!parser.isFinished()) {
            // incomplete notation
            return SAN::Result(std::make_shared<ParseError>(parser.consumed));
        }
        
        auto error = parser.buildAndValidateMove();
        if(error != nullptr) {
            return SAN::Result(error);
        }
        
        return SAN::Result(parser.m);
    }

}
