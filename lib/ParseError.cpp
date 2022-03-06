//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "ParseError.hpp"

namespace chessbox {
    std::string ParseError::description() const {
        if(file() != "") {
            return "Parse error at: " + file() + " (" + std::to_string(line()) + ":" + std::to_string(pos()) + ")";
        } else {
            return "Parse error at: " + std::to_string(pos());
        }
    }
}
