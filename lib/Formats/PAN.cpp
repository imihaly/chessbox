//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "PAN.hpp"
#include <cctype>
#include <string>
#include <sstream>
#include "AlgebraicNotation.hpp"
#include "Movecheck.hpp"


namespace chessbox {
    
    std::string PAN::notationForMove(const Position* position, const Move& move) {
        std::ostringstream os;
        os << move.from.notation() << move.to.notation();
        switch(move.promotion) {
            case Piece::Type::Rook:
                os << "R";
                break;
            case Piece::Type::Knight:
                os << "N";
                break;
            case Piece::Type::Bishop:
                os << "B";
                break;
            case Piece::Type::Queen:
                os << "Q";
                break;
            default:
                break;
        }
        return os.str();
    }
    
    struct PANParsingMachine {
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
#include "Grammar/PANGrammar.hpp"
        };
        
        PANParsingMachine(const Position *position): position(position) {}
        
        bool isFinished() {
            return  state == End;
        }
        
        std::shared_ptr<Error> buildAndValidateMove() {
            m = Move(Square(startFile, startRank), Square(endFile, endRank), promotionType);
            return Movecheck::isValidMove(position, m) ? nullptr : std::make_shared<SemanticError>("Decoded move (" + m.description() + ") is invalid in the given position!");
        }
        
        bool consume(char c) {
            consumed++;
            if (isspace(c)) return true;
            
            do {
                switch(state) {
#include "Grammar/GrammarDef.hpp"
#include "Grammar/PANGrammar.hpp"
                }
                
            } while(true);
            
            return false;
        }
        
    };
    
    PAN::Result PAN::moveFromNotation(const Position *position, const std::string notation) {
        PANParsingMachine parser(position);
        for(std::string::const_iterator it = notation.cbegin(); it != notation.cend(); ++it) {
            if(!parser.consume(*it)) {
                return PAN::Result(std::make_shared<ParseError>(parser.consumed));
            }
        }
        
        // end of notation
        if(!parser.consume(0)) {
            return PAN::Result(std::make_shared<ParseError>(parser.consumed));
        }
        
        if (!parser.isFinished()) {
            // incomplete notation
            return PAN::Result(std::make_shared<ParseError>(parser.consumed));
        }
        
        auto error = parser.buildAndValidateMove();
        if(error != nullptr) {
            return PAN::Result(error);
        }

        return PAN::Result(parser.m);
    }

}
