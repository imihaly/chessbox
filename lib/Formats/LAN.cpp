//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "LAN.hpp"
#include <cctype>
#include <string>
#include <sstream>
#include "AlgebraicNotation.hpp"
#include "Movecheck.hpp"

namespace chessbox {
        
    std::string LAN::notationForMove(const Position* position, const Move& move) {
        std::ostringstream os;
        if (!Movecheck::isValidMove(position, move)) {
            return "";
        }
        
        if (Movecheck::isKingsideCastleMove(position, move)) {
            os<<"O-O";
        } else if (Movecheck::isQueensideCastleMove(position, move)) {
            os<<"O-O-O";
        } else {
            os << symbolForPieceType(position->pieceOnSquare(move.from).type);
            os << move.from.notation();
            if(Movecheck::isCaptureMove(position, move)) {
                os << "x";
            } else {
                os << "-";
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

    struct LANParsingMachine {
        int state = 0;
        int consumed = 0;
        Piece::Type pieceType = Piece::Type::Pawn;
        Piece::Type promotionType = Piece::Type::None;;
        int startFile, startRank;
        int endFile, endRank;
        bool isCapture = false;
        bool isCheck = false;
        bool isMate = false;
        
        const Position *position;
        Move m;
        
        enum State {
            #include "Grammar/GrammarDecl.hpp"
            #include "Grammar/LANGrammar.hpp"
        };
        
        LANParsingMachine(const Position *position): position(position) {}

        bool isFinished() {
            return  state == End;
        }
                
        std::shared_ptr<Error> buildAndValidateMove() {
            m = Move(Square(startFile, startRank), Square(endFile, endRank), promotionType);
            return Movecheck::isValidMove(position, m) ? nullptr : std::make_shared<SemanticError>("Decoded move (" + m.description() + ") is invalid in the given position!");
        }
        
        void setShortCastle() {
            startFile = 'e' - 'a';
            endFile = 'g' - 'a';
            if(position->sideToMove() == Color::White) {
                endRank = startRank = 0;
            } else {
                endRank = startRank = 7;
            }
        }
        
        void setLongCastle() {
            startFile = 'e' - 'a';
            endFile = 'c' - 'a';
            if(position->sideToMove() == Color::White) {
                endRank = startRank = 0;
            } else {
                endRank = startRank = 7;
            }
        }

        bool consume(char c) {
            consumed++;
            if (isspace(c)) return true;
            
            do {
                switch(state) {
                    #include "Grammar/GrammarDef.hpp"
                    #include "Grammar/LANGrammar.hpp"
                }
                
            } while(true);
                        
            return false;
        }
    };
    
    LAN::Result LAN::moveFromNotation(const Position *position, const std::string notation) {
        LANParsingMachine parser(position);
        for(std::string::const_iterator it = notation.cbegin(); it != notation.cend(); ++it) {
            if(!parser.consume(*it)) {
                return LAN::Result(std::make_shared<ParseError>(parser.consumed));
            }
        }
        
        // end of notation
        if(!parser.consume(0)) {
            return LAN::Result(std::make_shared<ParseError>(parser.consumed));
        }
        
        if (!parser.isFinished()) {
            // incomplete notation
            return LAN::Result(std::make_shared<ParseError>(parser.consumed));
        }
        
        auto error = parser.buildAndValidateMove();
        if(error != nullptr) {
            return LAN::Result(error);
        }
        
        return LAN::Result(parser.m);
    }

}
