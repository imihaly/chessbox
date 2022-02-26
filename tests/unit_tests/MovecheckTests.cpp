//
// MovecheckTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Movecheck.hpp"
#include "UnitTesting.hpp"
#include "FEN.hpp"

// Helper method to validate that valid moves are and are only the ones landing on squares in `to`/
bool validMovesAre(Position* position, const Square& from, const Squares& to) {
    for(int idx = 0; idx < 64; idx++) {
        Square sq = Square(idx);
        if(Movecheck::isValidMove(position, Move(from, sq)) != to.contains(sq)) return  false;;
    }
    
    return true;
}

TEST(Movecheck, pawnMoveForward) {
    Position *pos = Position::basePosition();
    
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A2, Square::A3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B2, Square::B3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::C2, Square::C3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::D2, Square::D3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::E2, Square::E3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::F2, Square::F3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::G2, Square::G3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::H2, Square::H3)));
    
    pos->makeMove(Move(Square::B1, Square::C3));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B7, Square::B6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::C7, Square::C6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::D7, Square::D6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::E7, Square::E6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::F7, Square::F6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::G7, Square::G6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::H7, Square::H6)));
    
    delete pos;
}
TEST(Movecheck, pawnJumpForward) {
    Position *pos = Position::basePosition();
    
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A2, Square::A4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B2, Square::B4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::C2, Square::C4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::D2, Square::D4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::E2, Square::E4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::F2, Square::F4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::G2, Square::G4)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::H2, Square::H4)));

    pos->makeMove(Move(Square::B1, Square::C3));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B7, Square::B5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::C7, Square::C5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::D7, Square::D5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::E7, Square::E5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::F7, Square::F5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::G7, Square::G5)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::H7, Square::H5)));

    pos->makeMove(Move(Square::B8, Square::C6));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::C2, Square::C4))); // the knight is in way
    pos->makeMove(Move(Square::C3, Square::B1));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::C7, Square::C5))); // the knight is in way
    
    delete pos;
}
TEST(Movecheck, pawnPromotion) {
    Position *pos = new Position();
    pos->setPiece(Piece(Color::White, Piece::King), Square::E1);
    pos->setPiece(Piece(Color::Black, Piece::King), Square::E8);
    pos->setPiece(Piece(Color::White, Piece::Pawn), Square::A7);

    // Checking that a pawn reaching the last row promotes
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8)));
    
    // Checking that a pawn cannot promote neither to a pawn nor a king
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8, Piece::Pawn)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8, Piece::King)));
    
    // Checking valid promotions
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8, Piece::Rook)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8, Piece::Knight)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8, Piece::Bishop)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::A7, Square::A8, Piece::Queen)));
    delete pos;

    // checking that a pawn cannot promote without reaching the last rank
    pos = new Position();
    pos->setPiece(Piece(Color::White, Piece::King), Square::E1);
    pos->setPiece(Piece(Color::Black, Piece::King), Square::E8);
    pos->setPiece(Piece(Color::White, Piece::Pawn), Square::A6);

    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A6, Square::A7, Piece::Rook)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A6, Square::A7, Piece::Knight)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A6, Square::A7, Piece::Bishop)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::A6, Square::A7, Piece::Queen)));

    delete pos;
}
TEST(Movecheck, pawnCapture) {
    Position *pos = new Position();
    
    pos->setPiece(Piece(Color::White, Piece::Type::King), Square::E1);
    pos->setPiece(Piece(Color::Black, Piece::Type::King), Square::E8);
    
    pos->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::B2);
    pos->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::D2);
    pos->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::E2);
    pos->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::A3);
    pos->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::C3);
    
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B2, Square::A3)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B2, Square::C3)));

    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::D2, Square::C3)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::D2, Square::E3)));

    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::E2, Square::D3)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::E2, Square::F3)));

    delete pos;
}
TEST(Movecheck, enPassantCapture) {
    Position *pos = new Position();
    
    pos->setPiece(Piece(Color::White, Piece::Type::King), Square::E1);
    pos->setPiece(Piece(Color::Black, Piece::Type::King), Square::E8);
    
    pos->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::B5);
    pos->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::D5);
    pos->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::E5);
    pos->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::A5);
    pos->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::C5);
    pos->setEnPassantSquare(Square::C6);
    
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::B5, Square::A6)));
    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::B5, Square::C6)));

    CHECK_TRUE(Movecheck::isValidMove(pos, Move(Square::D5, Square::C6)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::D5, Square::E6)));

    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::E5, Square::D6)));
    CHECK_FALSE(Movecheck::isValidMove(pos, Move(Square::E5, Square::F6)));

    delete pos;
}

// MARK: - rook moves

TEST(Movecheck, rookGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4R3/8/8/5K2 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("4P3/4P3/4P3/4P3/PPPP1PPP/4P3/4P3/4P3 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}
TEST(Movecheck, rookObstruction) {
    Position *position = FEN::positionFromFEN("5k2/8/4n3/8/1P2R1p1/8/8/4K3 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/4P3/4P3/2PP1PP1/4P3/4P3/8 w - - 0 1");

    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}

// MARK: - knight moves

TEST(Movecheck, knightGeometry) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/4N3/8/8/4K3 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/3P1P2/2P3P1/8/2P3P1/3P1P2/8 w - - 0 1");

    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}
TEST(Movecheck, knightInCorner) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/N3K3 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/8/8/1P6/2P5/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::A1, validSquares));

    delete position;
}
TEST(Movecheck, knightOnBorder) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/N7/8/8/4K3 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/1P6/2P5/8/2P5/1P6/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::A4, validSquares));

    delete position;
}

// MARK: - bishop moves

TEST(Movecheck, bishopGeometry) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/4B3/8/8/4K3 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("P7/1P5P/2P3P1/3P1P2/8/3P1P2/2P3P1/1P5P w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}
TEST(Movecheck, bishopObstruction) {
    Position *position = FEN::positionFromFEN("4k3/7P/2n5/8/4B3/8/8/1b2K2R w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/2P3P1/3P1P2/8/3P1P2/2P3P1/1P6 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}

// MARK: - queen moves

TEST(Movecheck, queenGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4Q3/8/8/5K2 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("P3P3/1P2P2P/2P1P1P1/3PPP2/PPPP1PPP/3PPP2/2P1P1P1/1P2P2P w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}
TEST(Movecheck, queenObstruction) {
    Position *position = FEN::positionFromFEN("5k2/7P/2n5/8/1p2Q3/8/8/1b2K2R w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("4P3/4P3/2P1P1P1/3PPP2/1PPP1PPP/3PPP2/2P1P1P1/1P6 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}

// MARK: - king moves

TEST(Movecheck, kingGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4K3/8/8/8 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/3PPP2/3P1P2/3PPP2/8/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}
TEST(Movecheck, kingDoesntMovesIntoCheck) {
    Position *position = FEN::positionFromFEN("5k2/8/8/3r4/4K3/8/8/8 w - - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/3P4/5P2/4PP2/8/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E4, validSquares));

    delete position;
}
TEST(Movecheck, kingCastle) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/4K3 w KQkq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/8/8/8/3PPP2/2PP1PP1 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E1, validSquares));

    delete position;
}
TEST(Movecheck, blockedCastle1) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/R3KB1R w KQkq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/8/8/8/3PPP2/2PP4 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E1, validSquares));

    delete position;
}
TEST(Movecheck, blockedCastle2) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/R2QK2R w KQ - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/8/8/8/3PPP2/5PP1 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E1, validSquares));

    delete position;
}
TEST(Movecheck, blockedCastle3) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/R1B1K2R w KQ - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/8/8/8/3PPP2/3P1PP1 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E1, validSquares));

    delete position;
}
TEST(Movecheck, blockedCastle4) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/RN2K2R w KQ - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/8/8/8/8/8/3PPP2/3P1PP1 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E1, validSquares));

    delete position;
}
TEST(Movecheck, checkBlockedCastle1) {
    Position *position = FEN::positionFromFEN("r3k2r/8/4N3/8/8/8/8/4K3 b kq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("8/3PPP2/8/8/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E8, validSquares));

    delete position;
}
TEST(Movecheck, checkBlockedCastle2) {
    Position *position = FEN::positionFromFEN("r3k2r/8/7B/8/8/8/8/4K3 b kq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("2PP4/3PPP2/8/8/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E8, validSquares));

    delete position;
}
TEST(Movecheck, checkBlockedCastle3) {
    Position *position = FEN::positionFromFEN("r3k2r/8/7N/8/8/8/8/4K3 b kq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("2PP1P2/3PP3/8/8/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(validMovesAre(position, Square::E8, validSquares));

    delete position;
}
TEST(Movecheck, checkBlockedCastle4) {
    Position *position = FEN::positionFromFEN("r3k2r/8/B7/8/8/8/8/4K3 b kq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("3P1PP1/3PPP2/8/8/8/8/8/8 w - - 0 1");

    CHECK_TRUE(validMovesAre(position, Square::E8, validSquares));

    delete position;
}
TEST(Movecheck, checkBlockedCastle5) {
    Position *position = FEN::positionFromFEN("r3k2r/B7/8/8/8/8/8/4K3 b kq - 0 1");
    Squares validSquares = UnitTesting::squaresFromFEN("2PP1PP1/3PPP2/8/8/8/8/8/8 w - - 0 1");

    CHECK_TRUE(validMovesAre(position, Square::E8, validSquares));

    delete position;
}

// MARK: - helpers

TEST(Movecheck, detectChecks) {
    Position *position = FEN::positionFromFEN("r3k2r/B7/8/8/3b4/8/1B5P/K7 w - - 0 1");

    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::A7, Square::B6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::A3)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::C1)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::C3)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::H2, Square::H3)) == false);
}

TEST(Movecheck, kingMovingIntoRookCheck) {
    Position *position = FEN::positionFromFEN("5r1k/8/8/4K3/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F5)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F4)) == true);

    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D5)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E4)) == false);
}

TEST(Movecheck, kingMovingIntoQueenCheck) {
    Position *position = FEN::positionFromFEN("7k/5q2/8/4K3/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F5)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F4)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D5)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E4)) == false);
}

TEST(Movecheck, kingMovingIntoBishopCheck) {
    Position *position = FEN::positionFromFEN("7k/5b2/8/4K3/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F5)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D5)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E4)) == false);
}

TEST(Movecheck, kingMovingIntoPawnCheck) {
    Position *position = FEN::positionFromFEN("7k/5p2/8/4K3/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F5)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D5)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E4)) == false);
}

TEST(Movecheck, kingMovingIntoKnightCheck) {
    Position *position = FEN::positionFromFEN("7k/6n1/8/4K3/8/8/8/8 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F5)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::F4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D6)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D5)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::D4)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E5, Square::E4)) == false);
}

TEST(Movecheck, kingLeftInKnightCheck) {
    Position *position = FEN::positionFromFEN("7k/5n2/8/4K3/8/8/P7/8 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::A2, Square::A4)) == true);
}

TEST(Movecheck, kingInBlockedCheck) {
    Position *position = FEN::positionFromFEN("7k/8/8/8/3q4/4p3/P7/6K1 w - - 0 1");
    
    CHECK_FALSE(Movecheck::detectChecks(position, Move(Square::A2, Square::A4)) == true);
}

TEST(Movecheck, kingLeftInDiscoveredCheck) {
    Position *position = FEN::positionFromFEN("7k/8/8/8/3q4/8/PP6/K7 w - - 0 1");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::B3)));
}

TEST(Movecheck, kingLeftInDiscoveredCheck2) {
    Position *position = FEN::positionFromFEN("r2r2k1/p1q1pp1p/2p3p1/8/N1Q2n2/1P3PP1/P1P4P/1K1R3R b - - 0 20");
        
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::F7, Square::F6)));
}

TEST(Movecheck, kingLeftInCheck) {
    Position *position = FEN::positionFromFEN("3r2k1/p4p1p/2p3p1/4p3/2P5/1P3PP1/P1K1Q2P/3q4 w - - 0 30");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E2, Square::E1)));
}

