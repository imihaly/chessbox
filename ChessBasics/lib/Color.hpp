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

enum Color: int {
    White,
    Black
};

inline Color flip(Color c) {
    return Color(1 - c);
}

std::ostream& operator<<(std::ostream& os, const Color color);

#endif /* Color_hpp */
