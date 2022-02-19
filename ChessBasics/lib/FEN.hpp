//
// FEN.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef FEN_hpp
#define FEN_hpp

#include "deps.h"
#include "Position.hpp"

namespace chessbox {
    
    class FEN {
    public:
        static Position * positionFromFEN(std::string FEN, const char **parseErrorAt = NULL);
        static const std::string FENFromPosition(const Position *position, bool addMoveFields = true);
    };
    
}
#endif /* FEN_hpp */

