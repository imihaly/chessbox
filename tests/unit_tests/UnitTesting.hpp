//
// UnitTesting.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef UnitTesting_hpp
#define UnitTesting_hpp

// the unit testing fw
#include "tau/tau.h"
#include "Position.hpp"
#include "Square.hpp"
#include "Move.hpp"

using namespace chessbox;

class UnitTesting {
public:
    static Position *positionFromString(const char *string);
    static Squares squaresFromString(const char *string);
    static bool isEqual(Moves& op1, Moves& op2);
};

#endif /* UnitTesting_hpp */
