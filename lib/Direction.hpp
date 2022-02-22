//
// Direction.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Direction_hpp
#define Direction_hpp

#include "deps.h"

namespace chessbox {
    
    // represents the meaningfull directions on teh chessboard.
    enum Direction {
        Unknown = -2,
        Any = -1,
        North,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest,
        Count,
    };
    
    // Returns the opposite direction
    inline Direction opposite(Direction dir) {
        return Direction((dir + 4) % 8);
    };
    
} // namespace chessbox

#endif /* Direction_hpp */

