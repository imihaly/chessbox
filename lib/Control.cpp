//
// Control.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Control.hpp"
#include "Geometry.hpp"

namespace chessbox {
    
    Squares Control::squaresControlled(const Position *position, Color side) {
        Squares controlledSquares = 0;
        for(int idx = 0; idx < 64; idx++) {
            Square sq = Square(idx);
            if(position->pieceOnSquare(sq).color == side) {
                controlledSquares |= squaresControlled(position, sq);
            }
        }
        return controlledSquares;
    }
    Squares Control::squaresControlled(const Position *position, const Squares& squares) {
        Squares controlledSquares = 0;
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            controlledSquares |= squaresControlled(position, *it);
        }
        return controlledSquares;
    }
    
    Squares Control::squaresControlled(const Position *position, const Square square) {
        const Piece& piece = position->pieceOnSquare(square);
        Squares squares = 0;
        if(piece == Piece::NoPiece) return squares;
        
        Color color = piece.color;
        
        const Squares occupied = position->squaresOccupied();
        
        if (piece.type == Piece::Type::Pawn) {
            squares |= Geometry::pawnCaptures(square, color);
        } else if (piece.type == Piece::Type::Knight) {
            squares |= Geometry::knightDistances(square);
        } else if (piece.type == Piece::Type::King) {
            squares |= Geometry::adjacents(square);
        }
        
        if(piece.type == Piece::Type::Rook || piece.type == Piece::Type::Queen) {
            for(Direction dir: {Direction::North, Direction::East, Direction::South, Direction::West }) {
                squares |= Geometry::tillFirstByDir(square, dir, occupied);
            }
        }
        
        if(piece.type == Piece::Type::Bishop || piece.type == Piece::Type::Queen) {
            for(Direction dir: {Direction::NorthEast, Direction::SouthEast, Direction::SouthWest, Direction::NorthWest }) {
                squares |= Geometry::tillFirstByDir(square, dir, occupied);
            }
        }
        
        return squares;
    }
    
    Squares Control::squaresControlling(const Square square, const Position *position, Color side) {
        Squares squares = 0;
        
        squares |= rooksControlling(square, position, side);
        squares |= bishopsControlling(square, position, side);
        squares |= queensControlling(square, position, side);
        squares |= knightsControlling(square, position, side);
        squares |= pawnsControlling(square, position, side);
        squares |= kingsControlling(square, position, side);
        
        return squares;
    }
    Squares Control::rooksControlling(const Square square, const Position *position, Color side) {
        Squares squares = 0;
        Squares occupied = position->squaresOccupied();
        
        // rooks aligned with the square
        Squares rooks = position->squaresOccupied(side, Piece::Type::Rook);
        rooks &= Geometry::rookLines(square);
        for(Squares::Iterator it = rooks.begin(); it != rooks.end(); it++) {
            if((Geometry::range(*it, square) & occupied) == 0) {
                squares |= Geometry::bitboard(*it);
            }
        }
        
        return squares;
    }
    
    Squares Control::bishopsControlling(const Square square, const Position *position, Color side) {
        Squares squares = 0;
        Squares occupied = position->squaresOccupied();
        
        // rooks aligned with the square
        Squares bishops = position->squaresOccupied(side, Piece::Type::Bishop);
        bishops &= Geometry::rookLines(square);
        for(Squares::Iterator it = bishops.begin(); it != bishops.end(); it++) {
            if((Geometry::range(*it, square) & occupied) == 0) {
                squares |= Geometry::bitboard(*it);
            }
        }
        
        return squares;
    }
    
    Squares Control::queensControlling(const Square square, const Position *position, Color side) {
        Squares squares = 0;
        Squares occupied = position->squaresOccupied();
        
        // rooks aligned with the square
        Squares queens = position->squaresOccupied(side, Piece::Type::Queen);
        queens &= Geometry::lines(square);
        for(Squares::Iterator it = queens.begin(); it != queens.end(); it++) {
            if((Geometry::range(*it, square) & occupied) == 0) {
                squares |= Geometry::bitboard(*it);
            }
        }
        
        return squares;
        
    }
    
    Squares Control::knightsControlling(const Square square, const Position *position, Color side) {
        return position->squaresOccupied(side, Piece::Type::Knight) & Geometry::knightDistances(square);
    }
    
    Squares Control::pawnsControlling(const Square square, const Position *position, Color side) {
        return position->squaresOccupied(side, Piece::Type::Pawn) & Geometry::pawnCaptures(square, flip(side));
    }
    
    Squares Control::kingsControlling(const Square square, const Position *position, Color side) {
        return position->squaresOccupied(side, Piece::Type::King) & Geometry::adjacents(square);
    }
    
    Squares Control::squaresControlling(const Square square, const Position *position) {
        Squares ret = squaresControlling(square, position, Color::White);
        ret |= squaresControlling(square, position, Color::Black);
        return ret;
    }
    Squares Control::squaresControlling(const Squares& squares, const Position *position, Color side) {
        Squares ret = 0;
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            ret |= squaresControlling(*it, position, side);
        }
        return ret;
    }
    Squares Control::squaresControlling(const Squares& squares, const Position *position) {
        Squares ret = 0;
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            ret |= squaresControlling(*it, position);
        }
        return ret;
    }
    
    bool Control::isControlling(const Squares& squares, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded) {
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            if(isControlling(*it, position, side, piecesRemoved, piecesAdded)) return true;
        }
        return false;
    }
    
    bool Control::isControlling(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded) {
        
        if (isControllingByRookOrQueen(square, position, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByBishopOrQueen(square, position, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByKnight(square, position, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByPawn(square, position, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByKing(square, position, side, piecesRemoved, piecesAdded)) return true;
        
        return false;
    }
    
    bool Control::isControllingByRookOrQueen(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        // rooks and queens aligned with the square
        Squares rooksAndQueens = position->squaresOccupied(side, Piece::Type::Rook);
        rooksAndQueens |= position->squaresOccupied(side, Piece::Type::Queen);
        rooksAndQueens &= Geometry::rookLines(square);
        rooksAndQueens &= mask;
        rooksAndQueens &= ~changedSquares;
        for(Squares::Iterator it = rooksAndQueens.begin(); it != rooksAndQueens.end(); it++) {
            if((Geometry::range(*it, square) & occupied) == 0) {
                return true;
            }
        }
        
        return false;
    }
    
    bool Control::isControllingByBishopOrQueen(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares bishopsAndQueens = position->squaresOccupied(side, Piece::Type::Bishop);
        bishopsAndQueens |= position->squaresOccupied(side, Piece::Type::Queen);
        bishopsAndQueens &= Geometry::bishopLines(square);
        bishopsAndQueens &= mask;
        bishopsAndQueens &= ~changedSquares;
        
        for(Squares::Iterator it = bishopsAndQueens.begin(); it != bishopsAndQueens.end(); it++) {
            if((Geometry::range(*it, square) & occupied) == 0) {
                return true;
            }
        }
        return false;
    }
    
    bool Control::isControllingByKnight(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares attackingKnights = position->squaresOccupied(side, Piece::Type::Knight) & Geometry::knightDistances(square) & mask;
        attackingKnights &= ~changedSquares;
        
        if(attackingKnights) return true;
        
        return false;
    }
    
    bool Control::isControllingByPawn(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares attackingPawns = position->squaresOccupied(side, Piece::Type::Pawn) & Geometry::pawnCaptures(square, flip(side)) & mask;
        attackingPawns &= ~changedSquares;
        
        if(attackingPawns) return true;
        
        return false;
    }
    
    bool Control::isControllingByKing(const Square square, const Position *position, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares attackingKings = position->squaresOccupied(side, Piece::Type::King) & Geometry::adjacents(square) & mask;
        attackingKings &= ~changedSquares;
        
        if(attackingKings) return true;
        
        return false;
    }
    
}

