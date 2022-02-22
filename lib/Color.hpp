//
// Color.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include "deps.h"

namespace chessbox {
    
    // represents the two playing sides
    enum Color: int {
        White,
        Black
    };
    
    // returns the "other" color, the enemy.
    inline Color flip(Color c) {
        return Color(1 - c);
    }
    
} // namespace chessbox

std::ostream& operator<<(std::ostream& os, const chessbox::Color color);

#endif /* Color_hpp */
