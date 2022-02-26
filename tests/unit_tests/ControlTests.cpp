//
// ControlTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Control.hpp"
#include "UnitTesting.hpp"
#include "FEN.hpp"

TEST(Control, rookControl) {
    Position *position = FEN::positionFromFEN("8/8/8/4r3/8/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("4P3/4P3/4P3/PPPP1PPP/4P3/4P3/4P3/4P3 w - - 0 1");
    
    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, knightControl) {
    Position *position = FEN::positionFromFEN("8/8/8/4n3/8/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("8/3P1P2/2P3P1/8/2P3P1/3P1P2/8/8 w - - 0 1");

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, bishopControl) {
    Position *position = FEN::positionFromFEN("8/8/8/4b3/8/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("1P5P/2P3P1/3P1P2/8/3P1P2/2P3P1/1P5P/P7 w - - 0 1");

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, queenControl) {
    Position *position = FEN::positionFromFEN("8/8/8/4q3/8/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("1P2P2P/2P1P1P1/3PPP2/PPPP1PPP/3PPP2/2P1P1P1/1P2P2P/P3P3 w - - 0 1");

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, kingControl) {
    Position *position = FEN::positionFromFEN("8/8/8/4k3/8/8/8/8 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("8/8/3PPP2/3P1P2/3PPP2/8/8/8 w - - 0 1");
    
    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, pawnControl) {
    Position *position = FEN::positionFromFEN("8/pp1p2p1/8/7p/8/P2PP3/1P5P/8 w - - 0 1");
    Squares expectedWhite = UnitTesting::squaresFromFEN("8/8/8/8/1PPPPP2/P1P3P1/8/8 w - - 0 1");
    Squares expectedBlack = UnitTesting::squaresFromFEN("8/8/PPP1PP1P/8/6P1/8/8/8 w - - 0 1");

    Squares whiteControlledSquares = Control::squaresControlled(position, Color::White);
    CHECK_TRUE( whiteControlledSquares == expectedWhite);

    Squares blackControlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( blackControlledSquares == expectedBlack);
    
    delete position;
}
TEST(Control, complexControl) {
    Position *position = FEN::positionFromFEN("5k2/7P/2n5/8/1p2Q3/8/8/1b2K2R w - - 0 1");
    Squares expectedWhite = UnitTesting::squaresFromFEN("4P1P1/4P2P/2P1P1PP/3PPP1P/1PPP1PPP/3PPP1P/2PPPPPP/1P1PPPPP w - - 0 1");
    Squares expectedBlack = UnitTesting::squaresFromFEN("1P1PP1P1/P3PPP1/8/P3P3/1P1PP3/P1PP4/P1P5/8 w - - 0 1");

    Squares whiteControlledSquares = Control::squaresControlled(position, Color::White);
    CHECK_TRUE( whiteControlledSquares == expectedWhite);

    Squares blackControlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( blackControlledSquares == expectedBlack);
    
    delete position;
}
TEST(Control, controllingSquares) {
    Position *position = FEN::positionFromFEN("8/8/8/4r3/p2p1pn1/8/5P2/2q3b1 w - - 0 1");
    Squares expected = UnitTesting::squaresFromFEN("8/8/8/4P3/3P1PP1/8/8/2P5 w - - 0 1");
    
    Squares controlledSquares = Control::squaresControlling(position, Square::E3, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
