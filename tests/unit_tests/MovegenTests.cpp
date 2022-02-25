//
// MovegenTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
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
    
    Moves expected  = { Move(Square::E2, Square::E3), Move(Square::E2, Square::E4), Move(Square::E2, Square::D3), Move(Square::E2, Square::F3) };
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
    Moves expected  = { Move(Square::A7, Square::A8, Piece::Rook), Move(Square::A7, Square::A8, Piece::Knight), Move(Square::A7, Square::A8, Piece::Bishop), Move(Square::A7, Square::A8, Piece::Queen) };
    Moves moves     = Movegen::allMovesFrom(position, Square::A7);
    
    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

// MARK: - Rook moves

TEST(Movegen, rookGeometry) {
    Position *position = FEN::positionFromFEN("5k2/8/8/8/4R3/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::E1), Move(Square::E4, Square::E2), Move(Square::E4, Square::E3), Move(Square::E4, Square::E5), Move(Square::E4, Square::E6), Move(Square::E4, Square::E7), Move(Square::E4, Square::E8),
        Move(Square::E4, Square::A4), Move(Square::E4, Square::B4), Move(Square::E4, Square::C4), Move(Square::E4, Square::D4), Move(Square::E4, Square::F4), Move(Square::E4, Square::G4), Move(Square::E4, Square::H4)
    };
    Moves moves     = Movegen::allMovesFrom(position, Square::E4);

    CHECK_TRUE(UnitTesting::isEqual(moves, expected));
    
    delete position;
}

TEST(Movegen, rookCapturing) {
    Position *position = FEN::positionFromFEN("5k2/8/4p3/8/b3R1n1/8/8/5K2 w - - 0 1");
    Moves expected  = {
        Move(Square::E4, Square::E1), Move(Square::E4, Square::E2), Move(Square::E4, Square::E3), Move(Square::E4, Square::E5), Move(Square::E4, Square::E6),
        Move(Square::E4, Square::A4), Move(Square::E4, Square::B4), Move(Square::E4, Square::C4), Move(Square::E4, Square::D4), Move(Square::E4, Square::F4), Move(Square::E4, Square::G4)
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
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....B..."
                                                         "........"
                                                         "........"
                                                         ".....K.."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "x......."
                                                      ".x.....x"
                                                      "..x...x."
                                                      "...x.x.."
                                                      "....B..."
                                                      "...x.x.."
                                                      "..x...x."
                                                      ".x.....x"
                                                           );
    
    Moves moves;
    Movegen::allMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, bishopObstruction) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         ".......P"
                                                         "..n....."
                                                         "........"
                                                         "....B..."
                                                         "........"
                                                         "........"
                                                         ".b..K..R"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "..x...x."
                                                           "...x.x.."
                                                           "....B..."
                                                           "...x.x.."
                                                           "..x...x."
                                                           ".x......"
                                                           );
    Moves moves;
    Movegen::allMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);
    
    delete position;
}

TEST(Movegen, queenGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....Q..."
                                                         "........"
                                                         "........"
                                                         ".....K.."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "x...x..."
                                                      ".x..x..x"
                                                      "..x.x.x."
                                                      "...xxx.."
                                                      "xxxxQxxx"
                                                      "...xxx.."
                                                      "..x.x.x."
                                                      ".x..x..x"
                                                           );
    
    Moves moves;
    Movegen::allMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, queenObstruction) {
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
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "....x..."
                                                           "....x..."
                                                           "..x.x.x."
                                                           "...xxx.."
                                                           ".xxxQxxx"
                                                           "...xxx.."
                                                           "..x.x.x."
                                                           ".x......"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);
    
    delete position;
}

TEST(Movegen, kingGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "...xxx.."
                                                      "...xKx.."
                                                      "...xxx.."
                                                      "........"
                                                      "........"
                                                           );
    
    Moves moves;
    Movegen::allMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, kingDoesntMovesIntoCheck) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "...r...."
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...x...."
                                                          "....Kx.."
                                                          "....xx.."
                                                          "........"
                                                          "........"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, kingCastle) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setCastleKingside(Color::White, true);
    position->setCastleQueenside(Color::White, true);
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);

    Squares expected = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "..xxKxx."
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, blockedCastle1) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "R...KB.R"
                                                         );
    position->setCastleKingside(Color::White, true);
    position->setCastleQueenside(Color::White, true);
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);

    Squares expected = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "..xxK..."
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, blockedCastle2) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "R..QK..R"
                                                         );
    position->setCastleKingside(Color::White, true);
    position->setCastleQueenside(Color::White, true);

    Squares expected = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "....Kxx."
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, blockedCastle3) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "R.B.K..R"
                                                         );
    position->setCastleKingside(Color::White, true);
    position->setCastleQueenside(Color::White, true);

    Squares expected = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "...xKxx."
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, blockedCastle4) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "RN..K..R"
                                                         );
    position->setCastleKingside(Color::White, true);
    position->setCastleQueenside(Color::White, true);

    Squares expected = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "...xKxx."
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, checkBlockedCastle1) {
    Position *position = UnitTesting::positionFromString(
                                                         "r...k..r"
                                                         "........"
                                                         "....N..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);
    position->setSideToMove(Color::Black);

    Squares expected = UnitTesting::squaresFromString(
                                                          "....k..."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, checkBlockedCastle2) {
    Position *position = UnitTesting::positionFromString(
                                                         "r...k..r"
                                                         "........"
                                                         ".......B"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);
    position->setSideToMove(Color::Black);

    Squares expected = UnitTesting::squaresFromString(
                                                          "..xxk..."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, checkBlockedCastle3) {
    Position *position = UnitTesting::positionFromString(
                                                         "r...k..r"
                                                         "........"
                                                         ".......N"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);
    position->setSideToMove(Color::Black);

    Squares expected = UnitTesting::squaresFromString(
                                                          "..xxkx.."
                                                          "...xx..."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, checkBlockedCastle4) {
    Position *position = UnitTesting::positionFromString(
                                                         "r...k..r"
                                                         "........"
                                                         "B......."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);
    position->setSideToMove(Color::Black);

    Squares expected = UnitTesting::squaresFromString(
                                                          "...xkxx."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}
TEST(Movegen, checkBlockedCastle5) {
    Position *position = UnitTesting::positionFromString(
                                                         "r...k..r"
                                                         "B......."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setCastleKingside(Color::Black, true);
    position->setCastleQueenside(Color::Black, true);
    position->setSideToMove(Color::Black);

    Squares expected = UnitTesting::squaresFromString(
                                                          "..xxkxx."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    Moves moves;
    Movegen::allMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK_TRUE(landingSquares == expected);

    delete position;
}

TEST(Movegen, allPawnMovesTo) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....P..."
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "....x..."
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E3, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allPawnMovesTo_Jump) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....P..."
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "....x..."
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allPawnMovesTo_Capture) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....p..."
                                                         "...PPP.."
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "...x.x.."
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E3, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allPawnMovesTo_EnPassant) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "...PpP.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setEnPassantSquare(Square::E6);

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "...x.x.."
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E6, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}

TEST(Movegen, allRookMovesTo) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         ".R.....R"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      ".x..o..x"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allRookMovesTo_Blocked) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         ".R....pR"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      ".x..o..."
                                                      "........"
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allRookMovesTo_Capture) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         ".R..p..R"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      ".x..o..x"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}

TEST(Movegen, allKnightMovesTo) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "...N.N.."
                                                         "..N...N."
                                                         "........"
                                                         "..N...N."
                                                         "...N.N.."
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "...x.x.."
                                                      "..x...x."
                                                      "....o..."
                                                      "..x...x."
                                                      "...x.x.."
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allKnightMovesTo_Capture) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "...N.N.."
                                                         "..N...N."
                                                         "....q..."
                                                         "..N...N."
                                                         "...N.N.."
                                                         "....K..."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "...x.x.."
                                                      "..x...x."
                                                      "....o..."
                                                      "..x...x."
                                                      "...x.x.."
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}

TEST(Movegen, allBishopMovesTo) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..B"
                                                         "........"
                                                         ".B......"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "B...K.B."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      ".......x"
                                                      "........"
                                                      ".x......"
                                                      "........"
                                                      "...o...."
                                                      "........"
                                                      "........"
                                                      "x.....x."
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allBishopMovesTo_Blocked) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..B"
                                                         "........"
                                                         ".B......"
                                                         "..P.N..."
                                                         "........"
                                                         "..p.b..."
                                                         "........"
                                                         "B...K.B."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "...o...."
                                                      "........"
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allBishopMovesTo_Capture) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..B"
                                                         "........"
                                                         ".B......"
                                                         "........"
                                                         "...p...."
                                                         "........"
                                                         "........"
                                                         "B...K.B."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      ".......x"
                                                      "........"
                                                      ".x......"
                                                      "........"
                                                      "...o...."
                                                      "........"
                                                      "........"
                                                      "x.....x."
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}

TEST(Movegen, allQueenMovesTo) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..Q"
                                                         "...Q...."
                                                         ".Q......"
                                                         "........"
                                                         "Q.....Q."
                                                         "........"
                                                         "...Q...."
                                                         "Q...K.Q."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      ".......x"
                                                      "...x...."
                                                      ".x......"
                                                      "........"
                                                      "x..o..x."
                                                      "........"
                                                      "...x...."
                                                      "x.....x."
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allQueenMovesTo_Blocked) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..Q"
                                                         "........"
                                                         ".Q......"
                                                         "..P.N..."
                                                         "........"
                                                         "..p.b..."
                                                         "........"
                                                         "Q...K.Q."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "...o...."
                                                      "........"
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allQueenMovesTo_Capture) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..Q"
                                                         "........"
                                                         ".Q......"
                                                         "........"
                                                         "...p...."
                                                         "........"
                                                         "........"
                                                         "Q...K.Q."
                                                         );

    Squares expected = UnitTesting::squaresFromString(
                                                      ".......x"
                                                      "........"
                                                      ".x......"
                                                      "........"
                                                      "...o...."
                                                      "........"
                                                      "........"
                                                      "x.....x."
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}

TEST(Movegen, allKingMovesTo) {
    Position *position = UnitTesting::positionFromString(
                                                         "...k...."
                                                         "........"
                                                         "KKKKKKKK"
                                                         "KKKKKKKK"
                                                         "KKK.KKKK"
                                                         "KKKKKKKK"
                                                         "KKKKKKKK"
                                                         "........"
                                                         );
    position->setCastleKingside(Color::White, false);
    position->setCastleQueenside(Color::White, false);

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "..xxx..."
                                                      "..xox..."
                                                      "..xxx..."
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

    delete position;
}
TEST(Movegen, allKingMovesTo_Capture) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         "KKKKKKKK"
                                                         "KKKKKKKK"
                                                         "KKKpKKKK"
                                                         "KKKKKKKK"
                                                         "KKKKKKKK"
                                                         "........"
                                                         );
    position->setCastleKingside(Color::White, false);
    position->setCastleQueenside(Color::White, false);

    Squares expected = UnitTesting::squaresFromString(
                                                      "........"
                                                      "........"
                                                      "........"
                                                      "..xxx..."
                                                      "..xox..."
                                                      "..xxx..."
                                                      "........"
                                                      "........"
                                                      );


    Moves moves;
    Movegen::allMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK_TRUE(startingSquares == expected);

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



