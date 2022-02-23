//
// Movegen.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Movegen.hpp"
#include "Control.hpp"
#include "Movecheck.hpp"
#include "BB.hpp"

// MARK: - move generation

namespace chessbox {
    
    const Moves Movegen::allMovesFrom(Position *position, const Square from) {
        Moves result;
        allMovesFrom(position, from, result);
        return result;
    }
    
    const void Movegen::allMovesFrom(Position *position, const Square from, Moves& result) {
        const Piece& piece = position->pieceOnSquare(from);
        if (piece == Piece::NoPiece || piece.color != position->sideToMove()) {
            return;
        }
        
        switch(piece.type) {
            case Piece::Type::Pawn:
                return allPawnMovesFrom(position, from, result);
            case Piece::Type::Rook:
                return allRookMovesFrom(position, from, result);
            case Piece::Type::Knight:
                return allKnightMovesFrom(position, from, result);
            case Piece::Type::Bishop:
                return allBishopMovesFrom(position, from, result);
            case Piece::Type::Queen:
                return allQueenMovesFrom(position, from, result);
            case Piece::Type::King:
                return allKingMovesFrom(position, from, result);
            default:
                return;
        }
    }
    
    const Moves Movegen::allMovesTo(Position *position, const Square to) {
        Moves result;
        allMovesTo(position, to, result);
        return result;
    }
    
    const void Movegen::allMovesTo(Position *position, const Square to, Moves& result) {
        allPawnMovesTo(position, to, result);
        allRookMovesTo(position, to, result);
        allKnightMovesTo(position, to, result);
        allBishopMovesTo(position, to, result);
        allQueenMovesTo(position, to, result);
        allKingMovesTo(position, to, result);
    }
    
    const Moves Movegen::allMoves(Position *position) {
        Moves result;
        allMoves(position, result);
        return result;
    }
    
    const void Movegen::allMoves(Position *position, Moves& result) {
        const Squares squares = position->squaresOccupied(position->sideToMove());
        for(Squares::Iterator it = squares.begin(); it != squares.end(); it++) {
            allMovesFrom(position, *it, result);
        }
    }
    
// MARK: - helpers
    
    const void Movegen::movesToControlledSquares(Position *position, const Square from, Moves& result) {
        Squares controlledSquares = Control::squaresControlled(position, from);
        controlledSquares &= ~position->squaresOccupied(position->sideToMove());
        movesToSquares(position, from, controlledSquares, result);
    }
    
    const void Movegen::movesToSquares(Position *position, const Square from, const Squares& squaresTo, Moves& result) {
        const Piece& movingPiece = position->pieceOnSquare(from);
        for(Squares::Iterator it = squaresTo.begin(); it != squaresTo.end(); it++) {
            const Piece& piece = position->pieceOnSquare(*it);
            if(piece == Piece::NoPiece || (piece.color == flip(movingPiece.color) && piece.type != Piece::Type::King)) {
                Move move(from, *it);
                if(!Movecheck::detectChecks(position, move)) {
                    result += move;
                }
            }
        }
    }
    
    const void Movegen::allPawnMovesFrom(Position *position, const Square from, Moves& result) {
        assert(position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Pawn));
        
        Color side = position->sideToMove();
        Color other = flip(side);
        
        Squares captures = BB::pawnCaptures(from, side);
        Squares capturables = position->squaresOccupied(other);
        capturables.remove(position->kingPosition(other));
        if(position->enPassantSquare().isValid()) {
            capturables.add(position->enPassantSquare());
        }
        captures &= capturables;
        
        int endRow = position->sideToMove() == Color::White ? 7 : 0;
        
        for(Squares::Iterator it = captures.begin(); it != captures.end(); it++) {
            Move move(from, *it);
            bool isPromotionMove = (*it).row() == endRow;
            if (isPromotionMove) {
                Move move(from, *it, Piece::Type::Rook);
                if(!Movecheck::detectChecks(position, move)) {
                    result += move;
                    result += Move(from, *it, Piece::Type::Knight);
                    result += Move(from, *it, Piece::Type::Bishop);
                    result += Move(from, *it, Piece::Type::Queen);
                }
            } else {
                if(!Movecheck::detectChecks(position, move)) {
                    result += move;
                }
            }
        }
        
        Squares targets = BB::pawnMoves(from, side);
        targets &= ~position->squaresOccupied(); // limit targets to empty squares
        
        for(Squares::Iterator it = targets.begin(); it != targets.end(); it++) {
            bool isPromotionMove = (*it).row() == endRow;
            if (isPromotionMove) {
                Move move(from, *it, Piece::Type::Rook);
                if(!Movecheck::detectChecks(position, move)) {
                    result += move;
                    result += Move(from, *it, Piece::Type::Knight);
                    result += Move(from, *it, Piece::Type::Bishop);
                    result += Move(from, *it, Piece::Type::Queen);
                }
            } else {
                // checking if pawn is jumping
                int dr = (*it).row() - from.row();
                if (dr == -2 || dr == 2) {
                    int r = ((*it).row() + from.row())/2;
                    if (!position->isEmpty(Square(from.col(),  r))) continue;
                }
                Move move(from, *it);
                if(!Movecheck::detectChecks(position, move)) {
                    result += move;
                }
            }
        }
    }
    
    const void Movegen::allRookMovesFrom(Position *position, const Square from, Moves& result) {
        assert(position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Rook));
        
        movesToControlledSquares(position, from, result);
    }
    
    const void Movegen::allKnightMovesFrom(Position *position, const Square from, Moves& result) {
        assert(position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Knight));
        
        movesToControlledSquares(position, from, result);
    }
    
    const void Movegen::allBishopMovesFrom(Position *position, const Square from, Moves& result) {
        assert(position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Bishop));
        
        movesToControlledSquares(position, from, result);
    }
    
    const void Movegen::allQueenMovesFrom(Position *position, const Square from, Moves& result) {
        assert(position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Queen));
        
        movesToControlledSquares(position, from, result);
    }
    
    const void Movegen::allKingMovesFrom(Position *position, const Square from, Moves& result) {
        assert(position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::King));
        
        Squares controlledSquares = BB::adjacents(from);
        controlledSquares &= ~position->squaresOccupied(position->sideToMove());
        controlledSquares.remove(position->kingPosition(flip(position->sideToMove())));
        
        for(Squares::Iterator it = controlledSquares.begin(); it != controlledSquares.end(); it++) {
            Move move(from, *it);
            if (!Movecheck::detectChecks(position, move)) {
                result += move;
            }
        }
        
        // add castling moves if they are valid
        Move move(from, from + Step(2, 0));
        if(Movecheck::isValidMove(position, move)) {
            result += move;
        }
        Move move2(from, from + Step(-2, 0));
        if(Movecheck::isValidMove(position, move2)) {
            result += move2;
        }
    }
    
    const void Movegen::allPawnMovesTo(Position *position, const Square to, Moves& result) {
        if(!position->isEmpty(to) && position->pieceOnSquare(to).color == position->sideToMove()) {
            return;
        }
        
        Color us = position->sideToMove();
        Step forward = us == Color::White ? Step(0, 1) : Step(0, -1);
        
        {
            // simple pawn move
            Square from = to - forward;
            if (from.isValid() &&
                position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Pawn) &&
                Movecheck::precheckMove(position, Move(from, to)) &&
                Movecheck::isValidPawnMove(position, Move(from, to)))
            {
                result += Move(from, to);
            }
        }
        {
            // jump
            Square from = to - forward - forward;
            if (from.isValid() &&
                position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Pawn) &&
                Movecheck::precheckMove(position, Move(from, to)) &&
                Movecheck::isValidPawnMove(position, Move(from, to)))
            {
                result += Move(from, to);
            }
        }
        {
            // capture
            Square from = to - forward - Step(1, 0);
            if (from.isValid() &&
                position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Pawn) &&
                Movecheck::precheckMove(position, Move(from, to)) &&
                Movecheck::isValidPawnMove(position, Move(from, to)))
            {
                result += Move(from, to);
            }
        }
        {
            // capture
            Square from = to - forward + Step(1, 0);
            if (from.isValid() &&
                position->pieceOnSquare(from) == Piece(position->sideToMove(), Piece::Type::Pawn) &&
                Movecheck::precheckMove(position, Move(from, to)) &&
                Movecheck::isValidPawnMove(position, Move(from, to))) {
                result += Move(from, to);
            }
        }
    }
    
    const void Movegen::allRookMovesTo(Position *position, const Square to, Moves& result) {
        allLineMovesTo(position, to, Piece::Type::Rook, result);
    }
    
    const void Movegen::allKnightMovesTo(Position *position, const Square to, Moves& result) {
        Squares from = BB::knightDistances(to);
        from &= position->squaresOccupied(position->sideToMove(), Piece::Type::Knight);
        for(Squares::Iterator it = from.begin(); it != from.end(); ++it) {
            Move move(*it, to);
            if(Movecheck::isValidMove(position, move)) {
                result += move;
            }
        }
    }
    
    const void Movegen::allBishopMovesTo(Position *position, const Square to, Moves& result) {
        allLineMovesTo(position, to, Piece::Type::Bishop, result);
    }
    
    const void Movegen::allQueenMovesTo(Position *position, const Square to, Moves& result) {
        allLineMovesTo(position, to, Piece::Type::Queen, result);
    }
    
    const void Movegen::allKingMovesTo(Position *position, const Square to, Moves& result) {
        if(!position->isEmpty(to) && position->pieceOnSquare(to).color == position->sideToMove()) {
            return;
        }
        
        Color us = position->sideToMove();
        
        Squares from = BB::adjacents(to);
        from &= position->squaresOccupied(position->sideToMove(), Piece::Type::King);
        for(Squares::Iterator it = from.begin(); it != from.end(); ++it) {
            Move move(*it, to);
            if(Movecheck::isValidMove(position, move)) {
                result += move;
            }
        }
        
        do {
            if(position->canCastleKingside(us)) {
                Square from = to - Step(2, 0);
                if (!from.isValid()) break;
                if (position->pieceOnSquare(from) != Piece(us, Piece::Type::King)) break;
                
                Move move(from, to);
                if(Movecheck::isValidMove(position, move)) {
                    result += move;
                }
            }
        } while(false);
        
        do {
            if(position->canCastleQueenside(us)) {
                Square from = to + Step(2, 0);
                if (!from.isValid()) break;
                if (position->pieceOnSquare(from) != Piece(us, Piece::Type::King)) break;
                
                Move move(from, to);
                if(Movecheck::isValidMove(position, move)) {
                    result += move;
                }
            }
        } while(false);
    }
    
    const void Movegen::allLineMovesTo(Position *position, const Square to, Piece::Type type, Moves& result) {
        if(!position->isEmpty(to) && position->pieceOnSquare(to).color == position->sideToMove()) {
            return;
        }
        
        Squares from = position->squaresOccupied(position->sideToMove(), type);
        from &= BB::lines(to);
        
        for(Squares::Iterator it = from.begin(); it != from.end(); ++it) {
            Move move(*it, to);
            if(Movecheck::isValidMove(position, move)) {
                result += move;
            }
        }
    }
    
}  // namespace chessbox

