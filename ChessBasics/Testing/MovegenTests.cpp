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


#pragma mark - helpers

TEST(Movegen, pawnOnBaseline) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
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
                                                           "....x..."
                                                           "....x..."
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allPawnMovesFrom(position, Square::E2, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, pawnNotOnBaseline) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....P..."
                                                         "........"
                                                         "....K..."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "....x..."
                                                           "........"
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allPawnMovesFrom(position, Square::E3, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, pawnJumpBlocked) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....p..."
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
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allPawnMovesFrom(position, Square::E2, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, pawnBlocked) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....p..."
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
                                                           "....x..."
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allPawnMovesFrom(position, Square::E2, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, pawnCapturing) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "...p.b.."
                                                         "....P..."
                                                         "....K..."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "....x..."
                                                           "...xxx.."
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allPawnMovesFrom(position, Square::E2, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, pawnEnpassant) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         ".....pP."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    position->setEnPassantSquare(Square::F6);
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           ".....xx."
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allPawnMovesFrom(position, Square::G5, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, pawnPromotion) {
    Position *pos = new Position();
    pos->setPiece(Piece(Color::White, Piece::King), Square::E1);
    pos->setPiece(Piece(Color::Black, Piece::King), Square::E8);
    pos->setPiece(Piece(Color::White, Piece::Pawn), Square::A7);

    Moves moves;
    Movegen::allPawnMovesFrom(pos, Square::A7, moves);
    
    // Checking that a pawn reaching the last row promotes
    CHECK_FALSE(moves.contains(Move(Square::A7, Square::A8)));
    
    // Checking that a pawn cannot promote neither to a pawn nor a king
    CHECK_FALSE(moves.contains(Move(Square::A7, Square::A8, Piece::Pawn)));
    CHECK_FALSE(moves.contains(Move(Square::A7, Square::A8, Piece::King)));
    
    // Checking valid promotions
    CHECK_TRUE(moves.contains(Move(Square::A7, Square::A8, Piece::Rook)));
    CHECK_TRUE(moves.contains(Move(Square::A7, Square::A8, Piece::Knight)));
    CHECK_TRUE(moves.contains(Move(Square::A7, Square::A8, Piece::Bishop)));
    CHECK_TRUE(moves.contains(Move(Square::A7, Square::A8, Piece::Queen)));
    delete pos;

    // checking that a pawn cannot promote without reaching the last rank
    pos = new Position();
    pos->setPiece(Piece(Color::White, Piece::King), Square::E1);
    pos->setPiece(Piece(Color::Black, Piece::King), Square::E8);
    pos->setPiece(Piece(Color::White, Piece::Pawn), Square::A6);
    
    moves.clear();
    Movegen::allPawnMovesFrom(pos, Square::A6, moves);

    CHECK_TRUE(moves.contains(Move(Square::A6, Square::A7)));
    CHECK_FALSE(moves.contains(Move(Square::A6, Square::A7, Piece::Rook)));
    CHECK_FALSE(moves.contains(Move(Square::A6, Square::A7, Piece::Knight)));
    CHECK_FALSE(moves.contains(Move(Square::A6, Square::A7, Piece::Bishop)));
    CHECK_FALSE(moves.contains(Move(Square::A6, Square::A7, Piece::Queen)));

    delete pos;
}

TEST(Movegen, rookGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....R..."
                                                         "........"
                                                         "........"
                                                         ".....K.."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           "xxxxRxxx"
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           );
    

    Moves moves;
    Movegen::allRookMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, rookCapturing) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "....p..."
                                                         "........"
                                                         "b...R.n."
                                                         "........"
                                                         "........"
                                                         ".....K.."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "....x..."
                                                           "....x..."
                                                           "xxxxRxx."
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           );
    

    Moves moves;
    Movegen::allRookMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, rookObstructed) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "....P..."
                                                         "........"
                                                         "B...R.N."
                                                         "........"
                                                         "........"
                                                         ".....K.."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "....x..."
                                                           ".xxxRx.."
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           );
    

    Moves moves;
    Movegen::allRookMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}

TEST(Movegen, knightGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....N..."
                                                         "........"
                                                         "........"
                                                         ".....K.."
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "...x.x.."
                                                           "..x...x."
                                                           "....N..."
                                                           "..x...x."
                                                           "...x.x.."
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allKnightMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, knightCaptures) {
    Position *position = UnitTesting::positionFromString(
                                                         "K......."
                                                         "........"
                                                         ".....p.."
                                                         "......b."
                                                         "....N..."
                                                         "..r...n."
                                                         "...k.q.."
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "...x.x.."
                                                           "..x...x."
                                                           "....N..."
                                                           "..x...x."
                                                           ".....x.."
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allKnightMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}
TEST(Movegen, knightObstructed) {
    Position *position = UnitTesting::positionFromString(
                                                         "........"
                                                         "........"
                                                         ".....P.."
                                                         "......B."
                                                         "....N..."
                                                         "..R...N."
                                                         "...K.Q.."
                                                         "........"
                                                         );
    
    Squares expected = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "...x...."
                                                           "..x....."
                                                           "....N..."
                                                           "........"
                                                           "........"
                                                           "........"
                                                           );
    

    Moves moves;
    Movegen::allKnightMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
    delete position;
}

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
    Movegen::allBishopMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
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
    Movegen::allBishopMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
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
    Movegen::allQueenMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
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
    Movegen::allQueenMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
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
    Movegen::allKingMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
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
    Movegen::allKingMovesFrom(position, Square::E4, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);
    
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
    Movegen::allKingMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E1, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allKingMovesFrom(position, Square::E8, moves);
    Squares landingSquares = 0;
    for(Move move: moves) {
        landingSquares.add(move.to);
    }
    
    CHECK(landingSquares == expected);

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
    Movegen::allPawnMovesTo(position, Square::E3, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allPawnMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allPawnMovesTo(position, Square::E3, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allPawnMovesTo(position, Square::E6, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allRookMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allRookMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allRookMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allKnightMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allKnightMovesTo(position, Square::E4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allBishopMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allBishopMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allBishopMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allQueenMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allBishopMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allQueenMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allKingMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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
    Movegen::allKingMovesTo(position, Square::D4, moves);
    Squares startingSquares = 0;
    for(Move move: moves) {
        startingSquares.add(move.from);
    }
    
    CHECK(startingSquares == expected);

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



