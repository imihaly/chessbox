//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef LAN_hpp
#define LAN_hpp

#include <stdio.h>
#include <memory>
#include "Position.hpp"
#include "Result.hpp"
#include "ParseError.hpp"
#include "SemanticError.hpp"

namespace chessbox {
    class LAN {
    public:
        using Result = Result<Move, std::shared_ptr<Error>>;
        
    public:
        static std::string notationForMove(const Position* position, const Move& move);
        static Result moveFromNotation(const Position *position, const std::string notation);
    };
}


#endif /* LAN_hpp */
