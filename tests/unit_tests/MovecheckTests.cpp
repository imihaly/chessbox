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

#pragma mark - rook moves

TEST(Movecheck, rookGeometry) {
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
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           "xxxxRxxx"
                                                           "....x..."
                                                           "....x..."
                                                           "....x..."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, rookObstruction) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "....n..."
                                                         "........"
                                                         ".P..R.p."
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "....x..."
                                                           "....x..."
                                                           "..xxRxx."
                                                           "....x..."
                                                           "....x..."
                                                           "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}

#pragma mark - knight moves

TEST(Movecheck, knightGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....N..."
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "...x.x.."
                                                           "..x...x."
                                                           "....N..."
                                                           "..x...x."
                                                           "...x.x.."
                                                           "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, knightInCorner) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "N...K..."
                                                         );
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "....k..."
                                                           "........"
                                                           "........"
                                                           "........"
                                                           "........"
                                                           ".x......"
                                                           "..x....."
                                                           "N...K..."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::A1) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::A1, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, knightOnBorder) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "N......."
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "....k..."
                                                           "........"
                                                           ".x......"
                                                           "..x....."
                                                           "N......."
                                                           "..x....."
                                                           ".x......"
                                                           "....K..."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::A4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::A4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}

#pragma mark - bishop moves

TEST(Movecheck, bishopGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         "....k..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....B..."
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         );
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "x......."
                                                           ".x.....x"
                                                           "..x...x."
                                                           "...x.x.."
                                                           "....B..."
                                                           "...x.x.."
                                                           "..x...x."
                                                           ".x.....x"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, bishopObstruction) {
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
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "........"
                                                           "........"
                                                           "..x...x."
                                                           "...x.x.."
                                                           "....B..."
                                                           "...x.x.."
                                                           "..x...x."
                                                           ".x......"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            Move move = Move(Square::E4, sq);
            CHECK_TRUE(Movecheck::isValidMove(position, move) == validSquares.contains(sq));
        }
    }
    
    delete position;
}

#pragma mark - queen moves

TEST(Movecheck, queenGeometry) {
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
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "x...x..."
                                                           ".x..x..x"
                                                           "..x.x.x."
                                                           "...xxx.."
                                                           "xxxxQxxx"
                                                           "...xxx.."
                                                           "..x.x.x."
                                                           ".x..x..x"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, queenObstruction) {
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
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                           "....x..."
                                                           "....x..."
                                                           "..x.x.x."
                                                           "...xxx.."
                                                           ".xxxQxxx"
                                                           "...xxx.."
                                                           "..x.x.x."
                                                           ".x......"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        Move move = Move(Square::E4, sq);
        if (sq !=Square:: E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, move) == validSquares.contains(sq));
        }
    }
    
    delete position;
}

#pragma mark - king moves

TEST(Movecheck, kingGeometry) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....k.."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "...xKx.."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, kingDoesntMovesIntoCheck) {
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
    
    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...x...."
                                                          "....Kx.."
                                                          "....xx.."
                                                          "........"
                                                          "........"
                                                           );
    
    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E4) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E4, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, kingCastle) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "..xxKxx."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E1) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E1, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, blockedCastle1) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "..xxK..."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E1) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E1, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, blockedCastle2) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "....Kxx."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E1) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E1, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, blockedCastle3) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "...xKxx."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E1) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E1, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, blockedCastle4) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "...xxx.."
                                                          "...xKxx."
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E1) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E1, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, checkBlockedCastle1) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "....k..."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E8) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E8, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, checkBlockedCastle2) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "..xxk..."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E8) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E8, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, checkBlockedCastle3) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "..xxkx.."
                                                          "...xx..."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E8) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E8, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, checkBlockedCastle4) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "...xkxx."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E8) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E8, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}
TEST(Movecheck, checkBlockedCastle5) {
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

    Squares validSquares = UnitTesting::squaresFromString(
                                                          "..xxkxx."
                                                          "...xxx.."
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                          "........"
                                                           );
    

    for(int idx = 0; idx < Count; idx++) {
        Square sq = Square(idx);
        if (sq != Square::E8) {
            CHECK_TRUE(Movecheck::isValidMove(position, Move(Square::E8, sq)) == validSquares.contains(sq));
        }
    }
    
    delete position;
}

#pragma mark - helpers

TEST(Movecheck, detectChecks) {
    Position *position = UnitTesting::positionFromString(
                                                         "r...k..r"
                                                         "B......."
                                                         "........"
                                                         "........"
                                                         "...b...."
                                                         "........"
                                                         ".B.....P"
                                                         "K......."
                                                         );
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::A7, Square::B6)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::A3)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::C1)) == true);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::C3)) == false);
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::H2, Square::H3)) == false);
}

TEST(Movecheck, kingMovingIntoRookCheck) {
    Position *position = UnitTesting::positionFromString(
                                                         ".....r.k"
                                                         "........"
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
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
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         ".....q.."
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
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
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         ".....b.."
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                     );
    
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
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         ".....p.."
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
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
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         "......n."
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         );
    
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
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         ".....n.."
                                                         "........"
                                                         "....K..."
                                                         "........"
                                                         "........"
                                                         "P......."
                                                         "........"
                                                         );
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::A2, Square::A4)) == true);
}

TEST(Movecheck, kingInBlockedCheck) {
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "...q...."
                                                         "....p..."
                                                         "P......."
                                                         "......K."
                                                         );
    
    CHECK_FALSE(Movecheck::detectChecks(position, Move(Square::A2, Square::A4)) == true);
}

TEST(Movecheck, kingLeftInDiscoveredCheck) {
    Position *position = UnitTesting::positionFromString(
                                                         ".......k"
                                                         "........"
                                                         "........"
                                                         "........"
                                                         "...q...."
                                                         "........"
                                                         "PP......"
                                                         "K......."
                                                         );
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::B2, Square::B3)));
}

TEST(Movecheck, kingLeftInDiscoveredCheck2) {
    Position *position = FEN::positionFromFEN("r2r2k1/p1q1pp1p/2p3p1/8/N1Q2n2/1P3PP1/P1P4P/1K1R3R b - - 0 20");
        
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::F7, Square::F6)));
}

TEST(Movecheck, kingLeftInCheck) {
//    Position *position = UnitTesting::positionFromString(
//                                                         ".......k"
//                                                         "........"
//                                                         "........"
//                                                         "........"
//                                                         "........"
//                                                         "........"
//                                                         "..K.Q..."
//                                                         "...q...."
//                                                         );
    Position *position = FEN::positionFromFEN("3r2k1/p4p1p/2p3p1/4p3/2P5/1P3PP1/P1K1Q2P/3q4 w - - 0 30");
    
    CHECK_TRUE(Movecheck::detectChecks(position, Move(Square::E2, Square::E1)));
}

