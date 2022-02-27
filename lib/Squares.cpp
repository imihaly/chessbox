//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "Squares.hpp"

namespace chessbox {
    std::string Squares::description() const {
        std::string ret;
        for(Squares::Iterator it = begin(); it != end(); it++) {
            ret += (*it).notation() + " ";
        }
        return ret;
    }    
}  // namespace chessbox

