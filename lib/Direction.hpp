//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef Direction_hpp
#define Direction_hpp

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

