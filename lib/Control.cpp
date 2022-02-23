//
// Control.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Control.hpp"
#include "BB.hpp"

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
            squares |= BB::pawnCaptures(square, color);
        } else if (piece.type == Piece::Type::Knight) {
            squares |= BB::knightDistances(square);
        } else if (piece.type == Piece::Type::King) {
            squares |= BB::adjacents(square);
        }
        
        if(piece.type == Piece::Type::Rook || piece.type == Piece::Type::Queen) {
            for(Direction dir: {Direction::North, Direction::East, Direction::South, Direction::West }) {
                squares |= BB::tillFirstByDir(square, dir, occupied);
            }
        }
        
        if(piece.type == Piece::Type::Bishop || piece.type == Piece::Type::Queen) {
            for(Direction dir: {Direction::NorthEast, Direction::SouthEast, Direction::SouthWest, Direction::NorthWest }) {
                squares |= BB::tillFirstByDir(square, dir, occupied);
            }
        }
        
        return squares;
    }
    
    Squares Control::squaresControlling(const Position *position, const Square square, Color side) {
        Squares squares = 0;
        
        squares |= rooksControlling(position, square, side);
        squares |= bishopsControlling(position, square, side);
        squares |= queensControlling(position, square, side);
        squares |= knightsControlling(position, square, side);
        squares |= pawnsControlling(position, square, side);
        squares |= kingsControlling(position, square, side);
        
        return squares;
    }
    
    Squares Control::rooksControlling(const Position *position, const Square square, Color side) {
        Squares squares = 0;
        Squares occupied = position->squaresOccupied();
        
        // rooks aligned with the square
        Squares rooks = position->squaresOccupied(side, Piece::Type::Rook);
        rooks &= BB::rookLines(square);
        for(Squares::Iterator it = rooks.begin(); it != rooks.end(); it++) {
            if((BB::range(*it, square) & occupied) == 0) {
                squares |= BB::bitboard(*it);
            }
        }
        
        return squares;
    }
    
    Squares Control::bishopsControlling(const Position *position, const Square square, Color side) {
        Squares squares = 0;
        Squares occupied = position->squaresOccupied();
        
        // rooks aligned with the square
        Squares bishops = position->squaresOccupied(side, Piece::Type::Bishop);
        bishops &= BB::rookLines(square);
        for(Squares::Iterator it = bishops.begin(); it != bishops.end(); it++) {
            if((BB::range(*it, square) & occupied) == 0) {
                squares |= BB::bitboard(*it);
            }
        }
        
        return squares;
    }
    
    Squares Control::queensControlling(const Position *position, const Square square, Color side) {
        Squares squares = 0;
        Squares occupied = position->squaresOccupied();
        
        // rooks aligned with the square
        Squares queens = position->squaresOccupied(side, Piece::Type::Queen);
        queens &= BB::lines(square);
        for(Squares::Iterator it = queens.begin(); it != queens.end(); it++) {
            if((BB::range(*it, square) & occupied) == 0) {
                squares |= BB::bitboard(*it);
            }
        }
        
        return squares;
        
    }
    
    Squares Control::knightsControlling(const Position *position, const Square square, Color side) {
        return position->squaresOccupied(side, Piece::Type::Knight) & BB::knightDistances(square);
    }
    
    Squares Control::pawnsControlling(const Position *position, const Square square, Color side) {
        return position->squaresOccupied(side, Piece::Type::Pawn) & BB::pawnCaptures(square, flip(side));
    }
    
    Squares Control::kingsControlling(const Position *position, const Square square, Color side) {
        return position->squaresOccupied(side, Piece::Type::King) & BB::adjacents(square);
    }
    
    Squares Control::squaresControlling(const Position *position, const Square square) {
        Squares ret = squaresControlling(position, square, Color::White);
        ret |= squaresControlling(position, square, Color::Black);
        return ret;
    }
    Squares Control::squaresControlling(const Position *position, const Squares& squares, Color side) {
        Squares ret = 0;
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            ret |= squaresControlling(position, *it, side);
        }
        return ret;
    }
    Squares Control::squaresControlling(const Position *position, const Squares& squares) {
        Squares ret = 0;
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            ret |= squaresControlling(position, *it);
        }
        return ret;
    }
    
    bool Control::isControlling(const Position *position, const Squares& squares, Color side, const Squares& piecesRemoved, const Squares& piecesAdded) {
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            if(isControlling(position, *it, side, piecesRemoved, piecesAdded)) return true;
        }
        return false;
    }
    
    bool Control::isControlling(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded) {
        
        if (isControllingByRookOrQueen(position, square, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByBishopOrQueen(position, square, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByKnight(position, square, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByPawn(position, square, side, piecesRemoved, piecesAdded)) return true;
        if (isControllingByKing(position, square, side, piecesRemoved, piecesAdded)) return true;
        
        return false;
    }
    
    bool Control::isControllingByRookOrQueen(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        // rooks and queens aligned with the square
        Squares rooksAndQueens = position->squaresOccupied(side, Piece::Type::Rook);
        rooksAndQueens |= position->squaresOccupied(side, Piece::Type::Queen);
        rooksAndQueens &= BB::rookLines(square);
        rooksAndQueens &= mask;
        rooksAndQueens &= ~changedSquares;
        for(Squares::Iterator it = rooksAndQueens.begin(); it != rooksAndQueens.end(); it++) {
            if((BB::range(*it, square) & occupied) == 0) {
                return true;
            }
        }
        
        return false;
    }
    
    bool Control::isControllingByBishopOrQueen(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares bishopsAndQueens = position->squaresOccupied(side, Piece::Type::Bishop);
        bishopsAndQueens |= position->squaresOccupied(side, Piece::Type::Queen);
        bishopsAndQueens &= BB::bishopLines(square);
        bishopsAndQueens &= mask;
        bishopsAndQueens &= ~changedSquares;
        
        for(Squares::Iterator it = bishopsAndQueens.begin(); it != bishopsAndQueens.end(); it++) {
            if((BB::range(*it, square) & occupied) == 0) {
                return true;
            }
        }
        return false;
    }
    
    bool Control::isControllingByKnight(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares attackingKnights = position->squaresOccupied(side, Piece::Type::Knight) & BB::knightDistances(square) & mask;
        attackingKnights &= ~changedSquares;
        
        if(attackingKnights) return true;
        
        return false;
    }
    
    bool Control::isControllingByPawn(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares attackingPawns = position->squaresOccupied(side, Piece::Type::Pawn) & BB::pawnCaptures(square, flip(side)) & mask;
        attackingPawns &= ~changedSquares;
        
        if(attackingPawns) return true;
        
        return false;
    }
    
    bool Control::isControllingByKing(const Position *position, const Square square, Color side, const Squares& piecesRemoved, const Squares& piecesAdded, const Squares mask) {
        Squares occupied = position->squaresOccupied();
        
        occupied&= ~piecesRemoved;
        occupied |= piecesAdded;
        
        Squares changedSquares = piecesRemoved | piecesAdded;
        
        Squares attackingKings = position->squaresOccupied(side, Piece::Type::King) & BB::adjacents(square) & mask;
        attackingKings &= ~changedSquares;
        
        if(attackingKings) return true;
        
        return false;
    }
    
}  // namespace chessbox

