//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include <stdio.h>

#include "UnitTesting.hpp"
#include "Formats/SAN.hpp"
#include "Formats/FEN.hpp"

TEST(SAN, notationForSimpleMove) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE("e4" == SAN::notationForMove(position, Move(Square::E2, Square::E4)));
    CHECK_TRUE("Nc3" == SAN::notationForMove(position, Move(Square::B1, Square::C3)));
    
    delete position;
}

TEST(SAN, notationForPromotionMove) {
    Position *position = FEN::positionFromFEN("k7/5P2/8/8/8/8/8/K7 w - - 0 1");
    
    CHECK_TRUE("f8R+" == SAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Rook)));
    CHECK_TRUE("f8N" == SAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Knight)));
    CHECK_TRUE("f8B" == SAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Bishop)));
    CHECK_TRUE("f8Q+" == SAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Queen)));
    
    delete position;
}

TEST(SAN, notationForCaptureMove) {
    Position *position = FEN::positionFromFEN("k2n4/4P3/8/8/5p2/4P3/6N1/4K3 w - - 0 1");
    
    CHECK_TRUE("exd8R+" == SAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Rook)));
    CHECK_TRUE("exd8N" == SAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Knight)));
    CHECK_TRUE("exd8B" == SAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Bishop)));
    CHECK_TRUE("exd8Q+" == SAN::notationForMove(position, Move(Square::E7, Square::D8, Piece::Type::Queen)));
    
    CHECK_TRUE("exf4" == SAN::notationForMove(position, Move(Square::E3, Square::F4)));
    
    CHECK_TRUE("Nxf4" == SAN::notationForMove(position, Move(Square::G2, Square::F4)));
    delete position;
}

TEST(SAN, notationForCastling) {
    Position *position = FEN::positionFromFEN("3k4/8/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE("O-O" == SAN::notationForMove(position, Move(Square::E1, Square::G1)));
    CHECK_TRUE("O-O-O+" == SAN::notationForMove(position, Move(Square::E1, Square::C1)));
    delete position;
}

TEST(SAN, notationForMate) {
    Position *position = FEN::positionFromFEN("2rk4/2ppp3/8/8/8/8/8/4K2R w K - 0 1");
    
    CHECK_TRUE("Rh8#" == SAN::notationForMove(position, Move(Square::H1, Square::H8)));
    delete position;
}

TEST(SAN, notationForCaptureMate) {
    Position *position = FEN::positionFromFEN("2rkn3/2ppp3/3P1P2/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE("dxe7#" == SAN::notationForMove(position, Move(Square::D6, Square::E7)));
    delete position;
}

TEST(SAN, notationForPromotionMate) {
    Position *position = FEN::positionFromFEN("2rk4/2pppP2/8/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE("f8R#" == SAN::notationForMove(position, Move(Square::F7, Square::F8, Piece::Type::Rook)));
    delete position;
}

TEST(SAN, notationForCastlingMate) {
    Position *position = FEN::positionFromFEN("2rkr3/2p1p3/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE("O-O-O#" == SAN::notationForMove(position, Move(Square::E1, Square::C1)));
    delete position;
}

TEST(SAN, ambiguitiesSameRank) {
    Position *position = FEN::positionFromFEN("3k4/8/8/8/R6R/8/8/3K4 w - - 0 1");
    
    CHECK_TRUE("Rad4+" == SAN::notationForMove(position, Move(Square::A4, Square::D4)));
    CHECK_TRUE("Rhd4+" == SAN::notationForMove(position, Move(Square::H4, Square::D4)));
    delete position;
}

TEST(SAN, ambiguitiesSameFile) {
    Position *position = FEN::positionFromFEN("3k4/7R/8/8/7R/8/8/3K4 w - - 0 1");
    
    CHECK_TRUE("R7h6" == SAN::notationForMove(position, Move(Square::H7, Square::H6)));
    CHECK_TRUE("R4h6" == SAN::notationForMove(position, Move(Square::H4, Square::H6)));
    delete position;
}

TEST(SAN, ambiguitiesSameFileAndRank) {
    Position *position = FEN::positionFromFEN("3k4/2N1N3/5N2/8/1N3N2/2N1N3/8/3K4 w - - 0 1");
    
    CHECK_TRUE("Nc7d5" == SAN::notationForMove(position, Move(Square::C7, Square::D5)));
    CHECK_TRUE("Ne7d5" == SAN::notationForMove(position, Move(Square::E7, Square::D5)));
    CHECK_TRUE("N6d5" == SAN::notationForMove(position, Move(Square::F6, Square::D5)));
    delete position;
}

// MARK: - moveFromNotation tests

TEST(SAN, simpleMoveFromNotation) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(SAN::moveFromNotation(position, "e4").value() == Move(Square::E2, Square::E4));
    CHECK_TRUE(SAN::moveFromNotation(position, "Nc3").value() == Move(Square::B1, Square::C3));
    
    delete position;
}

TEST(SAN, promotionMoveFromNotation) {
    Position *position = FEN::positionFromFEN("k7/5P2/8/8/8/8/8/K7 w - - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "f8R+").value() == Move(Square::F7, Square::F8, Piece::Type::Rook));
    CHECK_TRUE(SAN::moveFromNotation(position, "f8N").value() == Move(Square::F7, Square::F8, Piece::Type::Knight));
    CHECK_TRUE(SAN::moveFromNotation(position, "f8B").value() == Move(Square::F7, Square::F8, Piece::Type::Bishop));
    CHECK_TRUE(SAN::moveFromNotation(position, "f8Q+").value() == Move(Square::F7, Square::F8, Piece::Type::Queen));
    
    delete position;
}

TEST(SAN, promotionMoveFromNotationWithAmbiguities) {
    Position *position = FEN::positionFromFEN("k3n3/3P1P2/8/8/8/8/8/K7 w - - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "dxe8R+").value() == Move(Square::D7, Square::E8, Piece::Type::Rook));
    CHECK_TRUE(SAN::moveFromNotation(position, "fxe8N").value() == Move(Square::F7, Square::E8, Piece::Type::Knight));
    
    delete position;
}

TEST(SAN, captureMoveFromNotation) {
    Position *position = FEN::positionFromFEN("k2n4/4P3/8/8/5p2/4P3/6N1/4K3 w - - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "exd8R+").value() == Move(Square::E7, Square::D8, Piece::Type::Rook));
    CHECK_TRUE(SAN::moveFromNotation(position, "exd8N").value() == Move(Square::E7, Square::D8, Piece::Type::Knight));
    CHECK_TRUE(SAN::moveFromNotation(position, "exd8B").value() == Move(Square::E7, Square::D8, Piece::Type::Bishop));
    CHECK_TRUE(SAN::moveFromNotation(position, "exd8Q+").value() == Move(Square::E7, Square::D8, Piece::Type::Queen));
    CHECK_TRUE(SAN::moveFromNotation(position, "exf4").value() == Move(Square::E3, Square::F4));
    CHECK_TRUE(SAN::moveFromNotation(position, "Nxf4").value() == Move(Square::G2, Square::F4));
    
    delete position;
}

TEST(SAN, captureMoveFromNotationWithAmbiguities) {
    Position *position = FEN::positionFromFEN("k2n4/4P3/6N1/8/5p2/4P3/4N1N1/4K3 w - - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "Nexf4").value() == Move(Square::E2, Square::F4));
    CHECK_TRUE(SAN::moveFromNotation(position, "N6xf4").value() == Move(Square::G6, Square::F4));
    CHECK_TRUE(SAN::moveFromNotation(position, "Ng2xf4").value() == Move(Square::G2, Square::F4));

    delete position;
}

TEST(SAN, castlingMoveFromNotation) {
    Position *position = FEN::positionFromFEN("3k4/8/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "O-O").value() == Move(Square::E1, Square::G1));
    CHECK_TRUE(SAN::moveFromNotation(position, "O-O-O+").value() == Move(Square::E1, Square::C1));
    
    delete position;
}

TEST(SAN, mateMoveFromNotation) {
    Position *position = FEN::positionFromFEN("2rk4/2ppp3/8/8/8/8/8/4K2R w K - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "Rh8#").value() == Move(Square::H1, Square::H8));
    
    delete position;
}

TEST(SAN, captureMateFromNotation) {
    Move m;
    Position *position = FEN::positionFromFEN("2rkn3/2ppp3/3P1P2/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "dxe7#").value() == Move(Square::D6, Square::E7));
    
    delete position;
}

TEST(SAN, promotionMateFromNotation) {
    Move m;
    Position *position = FEN::positionFromFEN("2rk4/2pppP2/8/8/8/8/8/4K3 w - - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "f8R#").value() == Move(Square::F7, Square::F8, Piece::Type::Rook));
    
    delete position;
}

TEST(SAN, castlingMateFromNotation) {
    Move m;
    Position *position = FEN::positionFromFEN("2rkr3/2p1p3/8/8/8/8/8/R3K2R w KQ - 0 1");
    
    CHECK_TRUE(SAN::moveFromNotation(position, "O-O-O#").value() == Move(Square::E1, Square::C1));
    
    delete position;
}

TEST(SAN, parseError) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(*SAN::moveFromNotation(position, "i4").error() == ParseError(1));
    CHECK_TRUE(*SAN::moveFromNotation(position, "x4").error() == ParseError(1));
    CHECK_TRUE(*SAN::moveFromNotation(position, "-4").error() == ParseError(1));
    CHECK_TRUE(*SAN::moveFromNotation(position, "2e ").error() == ParseError(1));
    CHECK_TRUE(*SAN::moveFromNotation(position, "+2").error() == ParseError(1));
    CHECK_TRUE(*SAN::moveFromNotation(position, "@2").error() == ParseError(1));
    CHECK_TRUE(*SAN::moveFromNotation(position, "nc3").error() == ParseError(1));

    CHECK_TRUE(*SAN::moveFromNotation(position, "NKB3").error() == ParseError(2));
    CHECK_TRUE(*SAN::moveFromNotation(position, "N0c").error() == ParseError(2));
    CHECK_TRUE(*SAN::moveFromNotation(position, "OO").error() == ParseError(2));
    CHECK_TRUE(*SAN::moveFromNotation(position, "00").error() == ParseError(2));

    CHECK_TRUE(*SAN::moveFromNotation(position, "ex3").error() == ParseError(3));
    CHECK_TRUE(*SAN::moveFromNotation(position, "0--0-0").error() == ParseError(3));
    CHECK_TRUE(*SAN::moveFromNotation(position, "O-0").error() == ParseError(3));
    CHECK_TRUE(*SAN::moveFromNotation(position, "0-O").error() == ParseError(3));
    
    CHECK_TRUE(*SAN::moveFromNotation(position, "Nbbc3").error() == ParseError(4));
    
    delete position;
}

TEST(SAN, semanticError) {
    Position *position = Position::basePosition();
    
    CHECK_TRUE(*SAN::moveFromNotation(position, "O-O").error() == SemanticError("Decoded move (e1-g1) is invalid in the given position!"));
    CHECK_TRUE(*SAN::moveFromNotation(position, "Nd3").error() == SemanticError("Could not find any move matching the specified criteria!"));

    delete position;
}

TEST(SAN, semanticError_Disambiguites) {
    Position *position = FEN::positionFromFEN("4k3/5R2/8/8/R7/8/5R2/4K3 w - - 0 1");
        
    CHECK_TRUE(*SAN::moveFromNotation(position, "Rbf4").error() == SemanticError("Could not find any move matching the specified criteria! Candidates were: f2-f4 a4-f4 f7-f4 "));
    
    delete position;
}

