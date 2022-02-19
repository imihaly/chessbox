//
// Squares.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Squares.hpp"

std::string Squares::description() const {
    std::string ret;
    for(Squares::Iterator it = begin(); it != end(); it++) {
        ret += (*it).description() + " ";
    }
    return ret;
}

std::ostream& operator<<(std::ostream& os, const Squares& squares) {
    os << squares.description();
    return os;
}
