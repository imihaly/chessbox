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

const Direction allDirections[] = {
    North,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest
};

// Returns the opposite direction
// for Any and Unknown returns themseves.
inline Direction opposite(Direction dir) {
    // optimisation
    // if (dir == Direction::Any || dir == Direction::Unknown) return dir;
    return Direction((dir + 4) % 8);
};

#endif /* Direction_hpp */
