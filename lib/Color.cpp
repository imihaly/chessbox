//
// Color.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "Color.hpp"

std::ostream& operator<<(std::ostream& os, const chessbox::Color color) {
    os << (color == chessbox::Color::White ? "white" : "black");
    return os;
}
