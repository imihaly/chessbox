//
// UnitTesting.hpp
//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).

//


#ifndef UnitTesting_hpp
#define UnitTesting_hpp

// the unit testing fw
#include "tau/tau.h"
#include "Position.hpp"
#include "Square.hpp"
#include "Squares.hpp"
#include "Move.hpp"

using namespace chessbox;

class UnitTesting {
public:
    static Squares squaresFromString(const char *string);
    static Squares squaresFromFEN(std::string FEN);

    static bool isEqual(Moves& op1, Moves& op2);
};

#endif /* UnitTesting_hpp */
