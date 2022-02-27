//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "UnitTesting.hpp"
#include "FEN.hpp"

TAU_NO_MAIN()

Squares UnitTesting::squaresFromFEN(std::string FEN) {
    Position *position = FEN::positionFromFEN(FEN);
    Squares squares = position->squaresOccupied();
    delete position;
    return squares;
}

bool UnitTesting::isEqual(Moves& op1, Moves& op2) {
    if (op1.size() != op2.size()) return false;
    for(Move m: op1) {
        if(!op2.contains(m)) return false;
    }
    return true;
}


