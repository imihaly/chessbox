//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "Formats/PAN.hpp"
#include "Formats/FEN.hpp"
#include "UnitTesting.hpp"

TEST(PAN, notationForSimpleMove) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE("e2e4" == PAN::notationForMove(position, Move(Square::E2, Square::E4)));
    CHECK_TRUE("b1c3" == PAN::notationForMove(position, Move(Square::B1, Square::C3)));

    delete position;
}

TEST(PAN, notationForPromotionMove) {
    Position *position = FEN::positionFromFEN("k7/5P2/8/8/8/8/8/K7 w - - 0 1");
    
    CHECK_TRUE("f7f8R" == PAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Rook)));
    CHECK_TRUE("f7f8N" == PAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Knight)));
    CHECK_TRUE("f7f8B" == PAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Bishop)));
    CHECK_TRUE("f7f8Q" == PAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Queen)));

    delete position;
}

TEST(PAN, fromNotationSimpleMove) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(PAN::moveFromNotation(position, "e2e4").value() == Move(Square::E2, Square::E4));
    CHECK_TRUE(PAN::moveFromNotation(position, "b1c3").value() == Move(Square::B1, Square::C3));
    
    delete position;
}

TEST(PAN, fromNotationPromotionMove) {
    Position *position = FEN::positionFromFEN("k7/5P2/8/8/8/8/8/K7 w - - 0 1");
    
    CHECK_TRUE(PAN::moveFromNotation(position, "f7f8R").value() == Move(Square::F7, Square::F8, Piece::Type::Rook));
    CHECK_TRUE(PAN::moveFromNotation(position, "f7f8N").value() == Move(Square::F7, Square::F8, Piece::Type::Knight));
    CHECK_TRUE(PAN::moveFromNotation(position, "f7f8B").value() == Move(Square::F7, Square::F8, Piece::Type::Bishop));
    CHECK_TRUE(PAN::moveFromNotation(position, "f7f8Q").value() == Move(Square::F7, Square::F8, Piece::Type::Queen));
    
    delete position;
}

TEST(PAN, parseError) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(*PAN::moveFromNotation(position, "i2e4").error() == ParseError(1));
    CHECK_TRUE(*PAN::moveFromNotation(position, "x2e4").error() == ParseError(1));
    CHECK_TRUE(*PAN::moveFromNotation(position, "-2e4").error() == ParseError(1));
    CHECK_TRUE(*PAN::moveFromNotation(position, "2e4 ").error() == ParseError(1));
    CHECK_TRUE(*PAN::moveFromNotation(position, "+2e4").error() == ParseError(1));
    CHECK_TRUE(*PAN::moveFromNotation(position, "@2e4").error() == ParseError(1));

    CHECK_TRUE(*PAN::moveFromNotation(position, "eae4").error() == ParseError(2));
    CHECK_TRUE(*PAN::moveFromNotation(position, "ebe4").error() == ParseError(2));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e0e4").error() == ParseError(2));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e9e4").error() == ParseError(2));

    CHECK_TRUE(*PAN::moveFromNotation(position, "e204").error() == ParseError(3));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e294").error() == ParseError(3));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2-4").error() == ParseError(3));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2+4").error() == ParseError(3));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2R4").error() == ParseError(3));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2N4").error() == ParseError(3));

    CHECK_TRUE(*PAN::moveFromNotation(position, "e2e0").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2e9").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2ea").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2ex").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2eK").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2e+").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, "e2e!").error() == ParseError(4));

    CHECK_TRUE(*PAN::moveFromNotation(position, "e2e").error() == ParseError(4));
    CHECK_TRUE(*PAN::moveFromNotation(position, " e2e").error() == ParseError(5));
    CHECK_TRUE(*PAN::moveFromNotation(position, " e2e ").error() == ParseError(6));

    delete position;
}

TEST(PAN, semanticError) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(*PAN::moveFromNotation(position, "b1d3").error() == SemanticError("Decoded move (b1-d3) is invalid in the given position!"));
    CHECK_TRUE(*PAN::moveFromNotation(position, "b1d2").error() == SemanticError("Decoded move (b1-d2) is invalid in the given position!"));
}
