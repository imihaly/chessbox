//
// ControlTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Control.hpp"
#include "UnitTesting.hpp"

TEST(Control, rookControl) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....r..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "....x..."
                                                      "....x..."
                                                      "....x..."
                                                      "xxxx.xxx"
                                                      "....x..."
                                                      "....x..."
                                                      "....x..."
                                                      "....x..."
                                                           );

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, knightControl) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....n..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "...x.x.."
                                                      "..x...x."
                                                      "........"
                                                      "..x...x."
                                                      "...x.x.."
                                                      "........"
                                                      "........"
                                                           );

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, bishopControl) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....b..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      ".x.....x"
                                                      "..x...x."
                                                      "...x.x.."
                                                      "........"
                                                      "...x.x.."
                                                      "..x...x."
                                                      ".x.....x"
                                                      "x......."
                                                           );

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, queenControl) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....q..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      ".x..x..x"
                                                      "..x.x.x."
                                                      "...xxx.."
                                                      "xxxx.xxx"
                                                      "...xxx.."
                                                      "..x.x.x."
                                                      ".x..x..x"
                                                      "x...x..."
                                                           );

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, kingControl) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "...xxx.."
                                                      "...x.x.."
                                                      "...xxx.."
                                                      "........"
                                                      "........"
                                                      "........"
                                                           );

    Squares controlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
TEST(Control, pawnControl) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "pp.p..p."
                                                         "........"
                                                         ".......p"
                                                         "........"
                                                         "P..PP..."
                                                         ".P.....P"
                                                         "........"
                                                         );
    
    Squares expectedWhite = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "........"
                                                           ".xxxxx.."
                                                           "x.x...x."
                                                           "........"
                                                           "........"
                                                           );

    Squares expectedBlack = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "xxx.xx.x"
                                                           "........"
                                                           "......x."
                                                           "........"
                                                           "........"
                                                           "........"
                                                           );

    Squares whiteControlledSquares = Control::squaresControlled(position, Color::White);
    CHECK_TRUE( whiteControlledSquares == expectedWhite);

    Squares blackControlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( blackControlledSquares == expectedBlack);
    
    delete position;
}
TEST(Control, complexControl) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         ".......P"
                                                         "..n....."
                                                         "........"
                                                         ".p..Q..."
                                                         "........"
                                                         "........"
                                                         ".b..K..R"
                                                         );
    
    Squares expectedWhite = UnitTesting::squaresFromString(
                                                      "....x.x."
                                                      "....x..x"
                                                      "..x.x.xx"
                                                      "...xxx.x"
                                                      ".xxx.xxx"
                                                      "...xxx.x"
                                                      "..xxxxxx"
                                                      ".x.xxxxx"
                                                           );

    Squares expectedBlack = UnitTesting::squaresFromString(
                                                           ".x.xx.x."
                                                           "x...xxx."
                                                           "........"
                                                           "x...x..."
                                                           ".x.xx..."
                                                           "x.xx...."
                                                           "x.x....."
                                                           "........"
                                                           );

    Squares whiteControlledSquares = Control::squaresControlled(position, Color::White);
    CHECK_TRUE( whiteControlledSquares == expectedWhite);

    Squares blackControlledSquares = Control::squaresControlled(position, Color::Black);
    CHECK_TRUE( blackControlledSquares == expectedBlack);
    
    delete position;
}
TEST(Control, controllingSquares) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....r..."
                                                         "p..p.pn."
                                                         "....T..."
                                                         ".....P.."
                                                         "..q...b."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "....x..."
                                                      "...x.xx."
                                                      "....T..."
                                                      "........"
                                                      "..x....."
                                                           );

    Squares controlledSquares = Control::squaresControlling(Square::E3, position, Color::Black);
    CHECK_TRUE( controlledSquares == expected);
    
    delete position;
}
