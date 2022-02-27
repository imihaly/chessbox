//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "Movegen.hpp"
#include "UnitTesting.hpp"
#include "FEN.hpp"


// MARK: - Pawn moves

TEST(Movegen, pawnOnBaseline) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/8/8/4P3/4K3 w - - 0 1");
    
    Moves expected  = { Move(Square::E2, Square::E3), Move(Square::E2, Square::E4) };
    Moves moves     = Movegen::allMovesFrom(position, Square::E2);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, pawnNotOnBaseline) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/8/4P3/8/4K3 w - - 0 1");

    Moves expected  = { Move(Square::E3, Square::E4) };
    Moves moves     = Movegen::allMovesFrom(position, Square::E3);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, pawnJumpBlocked) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/8/4p3/4P3/4K3 w - - 0 1");
    
    Moves expected  = { /* empty */ };
    Moves moves     = Movegen::allMovesFrom(position, Square::E2);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, pawnBlocked) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4p3/8/4P3/4K3 w - - 0 1");
    
    Moves expected  = { Move(Square::E2, Square::E3) };
    Moves moves     = Movegen::allMovesFrom(position, Square::E2);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, pawnCapturing) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/8/3p1b2/4P3/4K3 w - - 0 1");
    
    Moves expected  = { Move(Square::E2, Square::E3), Move(Square::E2, Square::E4), Move(Square::E2, Square::D3),
        Move(Square::E2, Square::F3) };
    Moves moves     = Movegen::allMovesFrom(position, Square::E2);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, pawnEnpassant) {
    Position *position = FEN::positionFromFEN("5k2/8/8/5pP1/8/8/8/4K3 w - f6 0 1");
    
    Moves expected  = { Move(Square::G5, Square::G6), Move(Square::G5, Square::F6)};
    Moves moves     = Movegen::allMovesFrom(position, Square::G5);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, pawnPromotion) {
    Position *position = FEN::positionFromFEN("4k3/P7/8/8/8/8/8/4K3 w - - 0 1");
    Moves expected  = { Move(Square::A7, Square::A8, Piece::Rook), Move(Square::A7, Square::A8, Piece::Knight),
        Move(Square::A7, Square::A8, Piece::Bishop), Move(Square::A7, Square::A8, Piece::Queen) };
    Moves moves     = Movegen::allMovesFrom(position, Square::A7);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

// MARK: - Rook moves

TEST(Movegen, rookGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4R3/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::E1), Move(Square::E4, Square::E2), Move(Square::E4, Square::E3), Move(Square::E4, Square::E5),
        Move(Square::E4, Square::E6), Move(Square::E4, Square::E7), Move(Square::E4, Square::E8),
        Move(Square::E4, Square::A4), Move(Square::E4, Square::B4), Move(Square::E4, Square::C4), Move(Square::E4, Square::D4),
        Move(Square::E4, Square::F4), Move(Square::E4, Square::G4), Move(Square::E4, Square::H4)
    };
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);

    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, rookCapturing) {
    Position *position = FEN::positionFromFEN("5k2/8/4p3/8/b3R1n1/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::E1), Move(Square::E4, Square::E2), Move(Square::E4, Square::E3), Move(Square::E4, Square::E5),
        Move(Square::E4, Square::E6),
        Move(Square::E4, Square::A4), Move(Square::E4, Square::B4), Move(Square::E4, Square::C4), Move(Square::E4, Square::D4),
        Move(Square::E4, Square::F4), Move(Square::E4, Square::G4)
    };
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, rookObstructed) {
    Position *position = FEN::positionFromFEN("5k2/8/4P3/8/B3R1N1/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::E1), Move(Square::E4, Square::E2), Move(Square::E4, Square::E3), Move(Square::E4, Square::E5),
        Move(Square::E4, Square::B4), Move(Square::E4, Square::C4), Move(Square::E4, Square::D4), Move(Square::E4, Square::F4)
    };
             
    Moves moves = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

// MARK: - Knight moves

TEST(Movegen, knightGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4N3/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::C5), Move(Square::E4, Square::D6), Move(Square::E4, Square::F6), Move(Square::E4, Square::G5),
        Move(Square::E4, Square::G3), Move(Square::E4, Square::F2), Move(Square::E4, Square::D2), Move(Square::E4, Square::C3),
    };
    
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, knightCaptures) {
    Position *position = FEN::positionFromFEN("K7/8/5p2/6b1/4N3/2r3n1/3k1q2/8 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::C5), Move(Square::E4, Square::D6), Move(Square::E4, Square::F6), Move(Square::E4, Square::G5),
        Move(Square::E4, Square::G3), Move(Square::E4, Square::F2), Move(Square::E4, Square::C3),
    };
    
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, knightObstructed) {
    Position *position = FEN::positionFromFEN("8/8/5P2/6B1/4N3/2R3N1/3K1Q2/8 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::C5), Move(Square::E4, Square::D6),
    };
    
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

// MARK: - Bishop moves

TEST(Movegen, bishopGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4B3/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::F5), Move(Square::E4, Square::G6), Move(Square::E4, Square::H7),
        Move(Square::E4, Square::F3), Move(Square::E4, Square::G2), Move(Square::E4, Square::H1),
        Move(Square::E4, Square::D5), Move(Square::E4, Square::C6), Move(Square::E4, Square::B7), Move(Square::E4, Square::A8),
        Move(Square::E4, Square::D3), Move(Square::E4, Square::C2), Move(Square::E4, Square::B1),
    };
    
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, bishopObstruction) {
    Position *position = FEN::positionFromFEN("4k3/7P/2n5/8/4B3/8/8/1b2K2R w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::F5), Move(Square::E4, Square::G6),
        Move(Square::E4, Square::F3), Move(Square::E4, Square::G2),
        Move(Square::E4, Square::D5), Move(Square::E4, Square::C6),
        Move(Square::E4, Square::D3), Move(Square::E4, Square::C2), Move(Square::E4, Square::B1),
    };
    
    Moves moves = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, queenGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4Q3/8/8/5K2 w - - 0 1");
    
    Moves expected = {
        Move(Square::E4, Square::B1), Move(Square::E4, Square::E1), Move(Square::E4, Square::H1), Move(Square::E4, Square::C2),
        Move(Square::E4, Square::E2), Move(Square::E4, Square::G2), Move(Square::E4, Square::D3), Move(Square::E4, Square::E3),
        Move(Square::E4, Square::F3), Move(Square::E4, Square::A4), Move(Square::E4, Square::B4), Move(Square::E4, Square::C4),
        Move(Square::E4, Square::D4), Move(Square::E4, Square::F4), Move(Square::E4, Square::G4), Move(Square::E4, Square::H4),
        Move(Square::E4, Square::D5), Move(Square::E4, Square::E5), Move(Square::E4, Square::F5), Move(Square::E4, Square::C6),
        Move(Square::E4, Square::E6), Move(Square::E4, Square::G6), Move(Square::E4, Square::B7), Move(Square::E4, Square::E7),
        Move(Square::E4, Square::H7), Move(Square::E4, Square::A8), Move(Square::E4, Square::E8),
    };

    Moves moves = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, queenObstruction) {
    Position *position = FEN::positionFromFEN("5k2/7P/2n5/8/1p2Q3/8/8/1b2K2R w - - 0 1");
    Moves expected = {
        Move(Square::E4, Square::B1), Move(Square::E4, Square::C2), Move(Square::E4, Square::E2), Move(Square::E4, Square::G2),
        Move(Square::E4, Square::D3), Move(Square::E4, Square::E3), Move(Square::E4, Square::F3), Move(Square::E4, Square::B4),
        Move(Square::E4, Square::C4), Move(Square::E4, Square::D4), Move(Square::E4, Square::F4), Move(Square::E4, Square::G4),
        Move(Square::E4, Square::H4), Move(Square::E4, Square::D5), Move(Square::E4, Square::E5), Move(Square::E4, Square::F5),
        Move(Square::E4, Square::C6), Move(Square::E4, Square::E6), Move(Square::E4, Square::G6), Move(Square::E4, Square::E7),
        Move(Square::E4, Square::E8),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, kingGeometry) {
    Position *position = FEN::positionFromFEN("8/8/8/8/4K3/8/8/8 w - - 0 1");
    Moves expected = {
        Move(Square::E4, Square::D3), Move(Square::E4, Square::E3), Move(Square::E4, Square::F3), Move(Square::E4, Square::D4),
        Move(Square::E4, Square::F4), Move(Square::E4, Square::D5), Move(Square::E4, Square::E5), Move(Square::E4, Square::F5),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, kingDoesntMovesIntoCheck) {
    Position *position = FEN::positionFromFEN("5k2/8/8/3r4/4K3/8/8/8 w - - 0 1");
    Moves expected = {
        Move(Square::E4, Square::E3), Move(Square::E4, Square::F3), Move(Square::E4, Square::F4), Move(Square::E4, Square::D5),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, kingCastle) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/4K3 w KQkq - 0 1");
    Moves expected = {
        Move(Square::E1, Square::C1), Move(Square::E1, Square::D1), Move(Square::E1, Square::F1), Move(Square::E1, Square::G1),
        Move(Square::E1, Square::D2), Move(Square::E1, Square::E2), Move(Square::E1, Square::F2),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E1);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, blockedCastle1) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/R3KB1R w KQkq - 0 1");
    Moves expected = {
        Move(Square::E1, Square::C1), Move(Square::E1, Square::D1), Move(Square::E1, Square::D2), Move(Square::E1, Square::E2),
        Move(Square::E1, Square::F2),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E1);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, blockedCastle2) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/R2QK2R w KQ - 0 1");
    Moves expected = {
        Move(Square::E1, Square::F1), Move(Square::E1, Square::G1), Move(Square::E1, Square::D2), Move(Square::E1, Square::E2),
        Move(Square::E1, Square::F2),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E1);

    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, blockedCastle3) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/R1B1K2R w KQ - 0 1");
    
    Moves expected = {
        Move(Square::E1, Square::D1), Move(Square::E1, Square::F1), Move(Square::E1, Square::G1), Move(Square::E1, Square::D2),
        Move(Square::E1, Square::E2), Move(Square::E1, Square::F2),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E1);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, blockedCastle4) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/8/RN2K2R w KQ - 0 1");
    Moves expected = {
        Move(Square::E1, Square::D1), Move(Square::E1, Square::F1), Move(Square::E1, Square::G1), Move(Square::E1, Square::D2),
        Move(Square::E1, Square::E2), Move(Square::E1, Square::F2),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E1);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, checkBlockedCastle1) {
    Position *position = FEN::positionFromFEN("r3k2r/8/4N3/8/8/8/8/4K3 b kq - 0 1");

    Moves expected = {
        Move(Square::E8, Square::D7), Move(Square::E8, Square::E7), Move(Square::E8, Square::F7),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E8);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, checkBlockedCastle2) {
    Position *position = FEN::positionFromFEN("r3k2r/8/7B/8/8/8/8/4K3 b kq - 0 1");

    Moves expected = {
        Move(Square::E8, Square::D7), Move(Square::E8, Square::E7), Move(Square::E8, Square::F7), Move(Square::E8, Square::C8),
        Move(Square::E8, Square::D8),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E8);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, checkBlockedCastle3) {
    Position *position = FEN::positionFromFEN("r3k2r/8/7N/8/8/8/8/4K3 b kq - 0 1");

    Moves expected = {
        Move(Square::E8, Square::D7), Move(Square::E8, Square::E7), Move(Square::E8, Square::C8), Move(Square::E8, Square::D8),
        Move(Square::E8, Square::F8),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E8);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
    }
TEST(Movegen, checkBlockedCastle4) {
    Position *position = FEN::positionFromFEN("r3k2r/8/B7/8/8/8/8/4K3 b kq - 0 1");

    Moves expected = {
        Move(Square::E8, Square::D7), Move(Square::E8, Square::E7), Move(Square::E8, Square::F7), Move(Square::E8, Square::D8),
        Move(Square::E8, Square::F8), Move(Square::E8, Square::G8),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E8);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, checkBlockedCastle5) {
    Position *position = FEN::positionFromFEN("r3k2r/B7/8/8/8/8/8/4K3 b kq - 0 1");
    Moves expected = {
        Move(Square::E8, Square::D7), Move(Square::E8, Square::E7), Move(Square::E8, Square::F7), Move(Square::E8, Square::C8),
        Move(Square::E8, Square::D8), Move(Square::E8, Square::F8), Move(Square::E8, Square::G8),
    };
    Moves moves = Movegen::allMovesFrom(position, Square::E8);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, allPawnMovesTo) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/4P3/4K3 w - - 0 1");

    Moves expected = {
        Move(Square::E2, Square::E3),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E3);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allPawnMovesTo_Jump) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/8/4P3/4K3 w - - 0 1");

    Moves expected = {
        Move(Square::E2, Square::E4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allPawnMovesTo_Capture) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/8/4p3/3PPP2/4K3 w - - 0 1");

    Moves expected = {
        Move(Square::D2, Square::E3), Move(Square::F2, Square::E3),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E3);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allPawnMovesTo_EnPassant) {
    Position *position = FEN::positionFromFEN("4k3/8/8/3PpP2/8/8/8/4K3 w - e6 0 1");

    Moves expected = {
        Move(Square::D5, Square::E6), Move(Square::F5, Square::E6),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E6);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, allRookMovesTo) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/1R5R/8/8/4K3 w - - 0 1");

    Moves expected = {
        Move(Square::B4, Square::E4), Move(Square::H4, Square::E4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allRookMovesTo_Blocked) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/1R4pR/8/8/4K3 w - - 0 1");
    Moves expected = {
        Move(Square::B4, Square::E4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allRookMovesTo_Capture) {
    Position *position = FEN::positionFromFEN("4k3/8/8/8/1R2p2R/8/8/4K3 w - - 0 1");
    Moves expected = {
        Move(Square::B4, Square::E4), Move(Square::H4, Square::E4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, allKnightMovesTo) {
    Position *position = FEN::positionFromFEN("4k3/8/3N1N2/2N3N1/8/2N3N1/3N1N2/4K3 w - - 0 1");
    Moves expected = {
        Move(Square::D2, Square::E4), Move(Square::F2, Square::E4), Move(Square::C3, Square::E4), Move(Square::G3, Square::E4),
        Move(Square::C5, Square::E4), Move(Square::G5, Square::E4), Move(Square::D6, Square::E4), Move(Square::F6, Square::E4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allKnightMovesTo_Capture) {
    Position *position = FEN::positionFromFEN("4k3/8/3N1N2/2N3N1/4q3/2N3N1/3N1N2/4K3 w - - 0 1");
    Moves expected = {
        Move(Square::D2, Square::E4), Move(Square::F2, Square::E4), Move(Square::C3, Square::E4), Move(Square::G3, Square::E4),
        Move(Square::C5, Square::E4), Move(Square::G5, Square::E4), Move(Square::D6, Square::E4), Move(Square::F6, Square::E4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::E4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, allBishopMovesTo) {
    Position *position = FEN::positionFromFEN("4k2B/8/1B6/8/8/8/8/B3K1B1 w - - 0 1");
    Moves expected = {
        Move(Square::A1, Square::D4), Move(Square::G1, Square::D4), Move(Square::B6, Square::D4), Move(Square::H8, Square::D4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allBishopMovesTo_Blocked) {
    Position *position = FEN::positionFromFEN("4k2B/8/1B6/2P1N3/8/2p1b3/8/B3K1B1 w - - 0 1");
    Moves expected = {
        
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allBishopMovesTo_Capture) {
    Position *position = FEN::positionFromFEN("4k2B/8/1B6/8/3p4/8/8/B3K1B1 w - - 0 1");
    Moves expected = {
        Move(Square::A1, Square::D4), Move(Square::G1, Square::D4), Move(Square::B6, Square::D4), Move(Square::H8, Square::D4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, allQueenMovesTo) {
    Position *position = FEN::positionFromFEN("4k2Q/3Q4/1Q6/8/Q5Q1/8/3Q4/Q3K1Q1 w - - 0 1");
    Moves expected = {
        Move(Square::A1, Square::D4), Move(Square::G1, Square::D4), Move(Square::D2, Square::D4), Move(Square::A4, Square::D4),
        Move(Square::G4, Square::D4), Move(Square::B6, Square::D4), Move(Square::D7, Square::D4), Move(Square::H8, Square::D4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allQueenMovesTo_Blocked) {
    Position *position = FEN::positionFromFEN("4k2Q/8/1Q6/2P1N3/8/2p1b3/8/Q3K1Q1 w - - 0 1");
    Moves expected = {
        
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allQueenMovesTo_Capture) {
    Position *position = FEN::positionFromFEN("4k2Q/8/1Q6/8/3p4/8/8/Q3K1Q1 w - - 0 1");
    Moves expected = {
        Move(Square::A1, Square::D4), Move(Square::G1, Square::D4), Move(Square::B6, Square::D4), Move(Square::H8, Square::D4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, allKingMovesTo) {
    Position *position = FEN::positionFromFEN("3k4/8/KKKKKKKK/KKKKKKKK/KKK1KKKK/KKKKKKKK/KKKKKKKK/8 w - - 0 1");
    Moves expected = {
        Move(Square::C3, Square::D4), Move(Square::D3, Square::D4), Move(Square::E3, Square::D4), Move(Square::C4, Square::D4),
        Move(Square::E4, Square::D4), Move(Square::C5, Square::D4), Move(Square::D5, Square::D4), Move(Square::E5, Square::D4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}
TEST(Movegen, allKingMovesTo_Capture) {
    Position *position = FEN::positionFromFEN("8/8/KKKKKKKK/KKKKKKKK/KKKpKKKK/KKKKKKKK/KKKKKKKK/8 w - - 0 1");
    Moves expected = {
        Move(Square::C3, Square::D4), Move(Square::D3, Square::D4), Move(Square::E3, Square::D4), Move(Square::C4, Square::D4),
        Move(Square::E4, Square::D4), Move(Square::C5, Square::D4), Move(Square::D5, Square::D4), Move(Square::E5, Square::D4),
    };
    Moves moves = Movegen::allMovesTo(position, Square::D4);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}


TEST(Movegen, Bug1) {
    Position *position = FEN::positionFromFEN("3r2k1/p4p1p/2p3p1/4p3/2P5/1P3PP1/P1K1Q2P/3q4 w - - 0 30");
    Moves moves;
    Movegen::allMoves(position, moves);
    
    CHECK_FALSE(moves.contains(Move(Square::E2, Square::E1)));
}

TEST(Movegen, Bug2) {
    Position *position = FEN::positionFromFEN("rnbqk1r1/pp3pP1/4p3/2p3p1/1bpP4/2N2N2/PP3PPP/R2QKB1R w KQq - 1 10");
    Moves moves;
    Movegen::allMovesFrom(position, Square::G7, moves);
    
    CHECK_FALSE(moves.contains(Move(Square::G7, Square::H8, Piece::Type::Rook)));
}

TEST(Movegen, Bug3) {
    Position *position = FEN::positionFromFEN("3r4/R6p/2p5/5pkp/3n1P1N/6P1/PP5K/8 b - f3 0 32");
    Moves moves;
    Movegen::allMovesFrom(position, Square::D4, moves);
    
    CHECK_FALSE(moves.contains(Move(Square::D4, Square::F3)));
}



