//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "UnitTesting.hpp"
#include "Formats/LAN.hpp"
#include "Formats/FEN.hpp"


TEST(LAN, notationForSimpleMove) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE("e2-e4" == LAN::notationForMove(position, Move(Square::E2, Square::E4)));
    CHECK_TRUE("Nb1-c3" == LAN::notationForMove(position, Move(Square::B1, Square::C3)));
    
    delete position;
}

TEST(LAN, notationForPromotionMove) {
    Position *position = FEN::positionFromFEN("k7/5P2/8/8/8/8/8/K7 w - - 0 1");
    
    CHECK_TRUE("f7-f8R+" == LAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Rook)));
    CHECK_TRUE("f7-f8N" == LAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Knight)));
    CHECK_TRUE("f7-f8B" == LAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Bishop)));
    CHECK_TRUE("f7-f8Q+" == LAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Queen)));
    
    delete position;
}

TEST(LAN, notationForCaptureMove) {
    Position *position = FEN::positionFromFEN("k2n4/4P3/8/8/5p2/4P3/6N1/4K3 w - - 0 1");
    
    CHECK_TRUE("e7xd8R+" == LAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Rook)));
    CHECK_TRUE("e7xd8N" == LAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Knight)));
    CHECK_TRUE("e7xd8B" == LAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Bishop)));
    CHECK_TRUE("e7xd8Q+" == LAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Queen)));
    
    CHECK_TRUE("e3xf4" == LAN::notationForMove(position, Move(Square::E3, Square::F4)));
    
    CHECK_TRUE("Ng2xf4" == LAN::notationForMove(position, Move(Square::G2, Square::F4)));
    delete position;
}

TEST(LAN, notationForCastling) {
    Position *position = FEN::positionFromFEN("3k4/8/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE("O-O" == LAN::notationForMove(position, Move(Square::E1, Square::G1)));
    CHECK_TRUE("O-O-O+" == LAN::notationForMove(position, Move(Square::E1, Square::C1)));
    delete position;
}

TEST(LAN, notationForMate) {
    Position *position = FEN::positionFromFEN("2rk4/2ppp3/8/8/8/8/8/4K2R w K - 0 1");
    
    CHECK_TRUE("Rh1-h8#" == LAN::notationForMove(position, Move(Square::H1, Square::H8)));
    delete position;
}

TEST(LAN, notationForCaptureMate) {
    Position *position = FEN::positionFromFEN("2rkn3/2ppp3/3P1P2/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE("d6xe7#" == LAN::notationForMove(position, Move(Square::D6, Square::E7)));
    delete position;
}

TEST(LAN, notationForPromotionMate) {
    Position *position = FEN::positionFromFEN("2rk4/2pppP2/8/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE("f7-f8R#" == LAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Rook)));
    delete position;
}

TEST(LAN, notationForCastlingMate) {
    Position *position = FEN::positionFromFEN("2rkr3/2p1p3/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE("O-O-O#" == LAN::notationForMove(position, Move(Square::E1, Square::C1)));
    delete position;
}


TEST(LAN, simpleMoveFromNotation) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(LAN::moveFromNotation(position, "e2-e4").value() == Move(Square::E2, Square::E4));
    CHECK_TRUE(LAN::moveFromNotation(position, "Nb1-c3").value() == Move(Square::B1, Square::C3));

    delete position;
}

TEST(LAN, promotionMoveFromNotation) {
    Position *position = FEN::positionFromFEN("k7/5P2/8/8/8/8/8/K7 w - - 0 1");

    CHECK_TRUE(LAN::moveFromNotation(position, "f7-f8R+").value() == Move(Square::F7, Square::F8, Piece::Type::Rook));
    CHECK_TRUE(LAN::moveFromNotation(position, "f7-f8N").value() == Move(Square::F7, Square::F8, Piece::Type::Knight));
    CHECK_TRUE(LAN::moveFromNotation(position, "f7-f8B").value() == Move(Square::F7, Square::F8, Piece::Type::Bishop));
    CHECK_TRUE(LAN::moveFromNotation(position, "f7-f8Q+").value() == Move(Square::F7, Square::F8, Piece::Type::Queen));
    
    delete position;
}

TEST(LAN, captureMoveFromNotation) {
    Position *position = FEN::positionFromFEN("k2n4/4P3/8/8/5p2/4P3/6N1/4K3 w - - 0 1");

    CHECK_TRUE(LAN::moveFromNotation(position, "e7xd8R+").value() == Move(Square::E7, Square::D8, Piece::Type::Rook));
    CHECK_TRUE(LAN::moveFromNotation(position, "e7xd8N").value() == Move(Square::E7, Square::D8, Piece::Type::Knight));
    CHECK_TRUE(LAN::moveFromNotation(position, "e7xd8B").value() == Move(Square::E7, Square::D8, Piece::Type::Bishop));
    CHECK_TRUE(LAN::moveFromNotation(position, "e7xd8Q+").value() == Move(Square::E7, Square::D8, Piece::Type::Queen));
    CHECK_TRUE(LAN::moveFromNotation(position, "e3xf4").value() == Move(Square::E3, Square::F4));
    CHECK_TRUE(LAN::moveFromNotation(position, "Ng2xf4").value() == Move(Square::G2, Square::F4));

    delete position;
}

TEST(LAN, castlingMoveFromNotation) {
    Position *position = FEN::positionFromFEN("3k4/8/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE(LAN::moveFromNotation(position, "O-O").value() == Move(Square::E1, Square::G1));
    CHECK_TRUE(LAN::moveFromNotation(position, "O-O-O+").value() == Move(Square::E1, Square::C1));

    delete position;
}

TEST(LAN, mateMoveFromNotation) {
    Position *position = FEN::positionFromFEN("2rk4/2ppp3/8/8/8/8/8/4K2R w K - 0 1");
    
    CHECK_TRUE(LAN::moveFromNotation(position, "Rh1-h8#").value() == Move(Square::H1, Square::H8));

    delete position;
}

TEST(LAN, captureMateFromNotation) {
    Position *position = FEN::positionFromFEN("2rkn3/2ppp3/3P1P2/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE(LAN::moveFromNotation(position, "d6xe7#").value() == Move(Square::D6, Square::E7));
    
    delete position;
}

TEST(LAN, promotionMateFromNotation) {
    Position *position = FEN::positionFromFEN("2rk4/2pppP2/8/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE(LAN::moveFromNotation(position, "f7-f8R#").value() == Move(Square::F7, Square::F8, Piece::Type::Rook));
    
    delete position;
}

TEST(LAN, castlingMateFromNotation) {
    Position *position = FEN::positionFromFEN("2rkr3/2p1p3/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE(LAN::moveFromNotation(position, "O-O-O#").value() == Move(Square::E1, Square::C1));
    
    delete position;
}

TEST(LAN, parseError) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(*LAN::moveFromNotation(position, "i2-e4").error() == ParseError(1));
    CHECK_TRUE(*LAN::moveFromNotation(position, "x2-e4").error() == ParseError(1));
    CHECK_TRUE(*LAN::moveFromNotation(position, "-2-e4").error() == ParseError(1));
    CHECK_TRUE(*LAN::moveFromNotation(position, "2-e4 ").error() == ParseError(1));
    CHECK_TRUE(*LAN::moveFromNotation(position, "+2-e4").error() == ParseError(1));
    CHECK_TRUE(*LAN::moveFromNotation(position, "@2-e4").error() == ParseError(1));
    
    CHECK_TRUE(*LAN::moveFromNotation(position, "ea-e4").error() == ParseError(2));
    CHECK_TRUE(*LAN::moveFromNotation(position, "eb-e4").error() == ParseError(2));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e0-e4").error() == ParseError(2));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e9-e4").error() == ParseError(2));

    CHECK_TRUE(*LAN::moveFromNotation(position, "e2+e4").error() == ParseError(3));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2=e4").error() == ParseError(3));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2!e4").error() == ParseError(3));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2?e4").error() == ParseError(3));

    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-04").error() == ParseError(4));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-94").error() == ParseError(4));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2--4").error() == ParseError(4));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-+4").error() == ParseError(4));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-R4").error() == ParseError(4));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-N4").error() == ParseError(4));
    
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-e0").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-e9").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-ea").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-ex").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-eK").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-e+").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-e!").error() == ParseError(5));
    
    CHECK_TRUE(*LAN::moveFromNotation(position, "e2-e").error() == ParseError(5));
    CHECK_TRUE(*LAN::moveFromNotation(position, " e2-e").error() == ParseError(6));
    CHECK_TRUE(*LAN::moveFromNotation(position, " e2-e ").error() == ParseError(7));
    
    delete position;
}

TEST(PAN, semanticError) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(*LAN::moveFromNotation(position, "O-O").error() == SemanticError("Decoded move (e1-g1) is invalid in the given position!"));
    CHECK_TRUE(*LAN::moveFromNotation(position, "O-O-O").error() == SemanticError("Decoded move (e1-c1) is invalid in the given position!"));
    CHECK_TRUE(*LAN::moveFromNotation(position, "b1-d3").error() == SemanticError("Decoded move (b1-d3) is invalid in the given position!"));
    CHECK_TRUE(*LAN::moveFromNotation(position, "b1-d2").error() == SemanticError("Decoded move (b1-d2) is invalid in the given position!"));
}
