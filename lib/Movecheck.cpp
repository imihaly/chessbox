//
// Movecheck.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Movecheck.hpp"
#include "Control.hpp"
#include "BB.hpp"

namespace chessbox {
    bool Movecheck::isValidMove(const Position *position, const Move& move) {
        if(!precheckMove(position, move)) return false;
        switch(position->pieceOnSquare(move.from).type) {
            case Piece::Type::Pawn:
                if(!isValidPawnMove(position, move)) return false;
                break;
            case Piece::Type::Rook:
                if(!isValidRookMove(position, move)) return false;
                break;
            case Piece::Type::Knight:
                if(!isValidKnightMove(position, move)) return false;
                break;
            case Piece::Type::Bishop:
                if(!isValidBishopMove(position, move)) return false;
                break;
            case Piece::Type::Queen:
                if(!isValidQueenMove(position, move)) return false;
                break;
            case Piece::Type::King:
                if(!isValidKingMove(position, move)) return false;
                break;
            default:
                return false;
        }
        return !detectChecks(position, move);
    }
    
    bool Movecheck::isValidPawnMove(const Position *position, const Move& move) {
        // checking promotion status
        int baseRow = position->sideToMove() == Color::White ? 1 : 6;
        int endRow = position->sideToMove() == Color::White ? 7 : 0;
        bool isPromotionMove = move.to.row() == endRow;
        int dir = position->sideToMove() == Color::White ? 1 : -1;
        
        bool looksLikeACapture = move.to.row() - move.from.row() == dir && std::abs(move.to.col() - move.from.col()) == 1;
        
        // checking promotion setup
        if(isPromotionMove) {
            if (!isValidPromotionType(move.promotion)) return false;
        } else {
            if (move.promotion != Piece::Type::None) return false;
        }
        
        // check if it is a simple move forward
        if(move.to.col() == move.from.col() && move.to.row() - move.from.row() == dir && position->isEmpty(move.to)) {
            return true;
        }
        
        // check if it is a jump forward
        Square midSquare = Square(move.from.col(), move.from.row() + dir);
        if(move.from.row() == baseRow &&
           move.to.col() == move.from.col() &&
           move.to.row() - move.from.row() == 2 * dir &&
           position->isEmpty(move.to) &&
           position->isEmpty(midSquare)) {
            return true;
        }
        
        // check if en-passant
        if(looksLikeACapture && move.to == position->enPassantSquare()) {
            return true;
        }
        
        // check if it is a simple capture
        if(looksLikeACapture) {
            // check that there is an enemy piece on the landing square
            const Piece& pieceOnLandingSquare = position->pieceOnSquare(move.to);
            return pieceOnLandingSquare != Piece::NoPiece;
        }
        
        return false;
    }
    
// MARK: - rook moves
    
    bool Movecheck::isValidRookMove(const Position *position, const Move& move) {
        int dRow = move.to.row() - move.from.row();
        int dCol = move.to.col() - move.from.col();
        if (dRow != 0 && dCol != 0) return false;
        
        const Squares& occupied = position->squaresOccupied();
        return (0 == (BB::range(move.from, move.to) & occupied));
    }
    
// MARK: - knoght moves
    
    bool Movecheck::isValidKnightMove(const Position *position, const Move& move) {
        // checking the geometry
        int dRow = std::abs(move.to.row() - move.from.row());
        if(dRow != 1 && dRow != 2) return false;
        
        int dCol = std::abs(move.to.col() - move.from.col());
        if(dCol != 1 && dCol != 2) return false;
        
        if(dRow + dCol != 3) return false;
        
        return true;
    }
    
// MARK: - bishop moves
    
    bool Movecheck::isValidBishopMove(const Position *position, const Move& move) {
        int dRow = move.to.row() - move.from.row();
        int dCol = move.to.col() - move.from.col();
        
        if(dRow != dCol && dRow != -dCol) return  false;
        
        const Squares& occupied = position->squaresOccupied();
        return (0 == (BB::range(move.from, move.to) & occupied));
    }
    
// MARK: - queen moves
    
    bool Movecheck::isValidQueenMove(const Position *position, const Move& move) {
        int dRow = move.to.row() - move.from.row();
        int dCol = move.to.col() - move.from.col();
        
        if(dRow != 0 && dCol != 0 && dRow != dCol && dRow != -dCol) return  false;
        
        const Squares& occupied = position->squaresOccupied();
        return (0 == (BB::range(move.from, move.to) & occupied));
    }
    
// MARK: - king moves
    
    bool Movecheck::isValidKingMove(const Position *position, const Move& move) {
        Color us = position->sideToMove();
        
        Step diff = move.step();
        if (diff == Step(2, 0)) {
            // 0-0
            if (!position->canCastleKingside(us)) return false;
            
            Squares occupied = position->squaresOccupied();
            Squares ooSquares = BB::ooFreeRange(us);
            if (occupied & ooSquares) return false;
            
            Squares toCheck = BB::ooUncontrolledRange(us);
            
            return !Control::isControlling(position, toCheck, flip(us));
        }
        
        if (diff == Step(-2, 0)) {
            // 0-0-0
            
            if (!position->canCastleQueenside(us)) return false;
            
            Squares occupied = position->squaresOccupied();
            Squares oooSquares = BB::oooFreeRange(us);
            if (occupied & oooSquares) return false;
            
            Squares toCheck = BB::oooUncontrolledRange(us);
            
            return !Control::isControlling(position, toCheck, flip(us));
        }
        
        Step s = move.step();
        if(std::abs(s.dRow) > 1 || std::abs(s.dCol) > 1) return  false;
        
        return true;
    }
    
// MARK: - helpers
    
    bool Movecheck::isValidPromotionType(Piece::Type type) {
        switch(type) {
            case Piece::Type::Rook:
            case Piece::Type::Knight:
            case Piece::Type::Bishop:
            case Piece::Type::Queen:
                return true;
            default:
                return false;
        }
    }
    
    bool Movecheck::isCapturableType(Piece::Type type) {
        switch(type) {
            case Piece::Type::Pawn:
            case Piece::Type::Rook:
            case Piece::Type::Knight:
            case Piece::Type::Bishop:
            case Piece::Type::Queen:
                return true;
            default:
                return false;
        }
    }
    
    bool Movecheck::precheckMove(const Position *position, const Move& move) {
        if(move.from == move.to) return false;
        if (move.from == Square::None || move.to == Square::None) return false;
        
        const Piece& movingPiece = position->pieceOnSquare(move.from);
        if(movingPiece == Piece::NoPiece) return false;
        if (movingPiece.color != position->sideToMove()) return false;
        
        const Piece& pieceOnLandingSquare = position->pieceOnSquare(move.to);
        if(pieceOnLandingSquare != Piece::NoPiece) {
            if(!isCapturableType(pieceOnLandingSquare.type) || pieceOnLandingSquare.color == position->sideToMove()) {
                return false;
            }
        }
        
        return true;
    }
    
    bool Movecheck::detectChecks(const Position *position, const Move& move) {
        Color side = position->sideToMove();
        
        Squares removed =  BB::bitboard(move.from);
        if (move.to == position->enPassantSquare() && position->pieceOnSquare(move.from).type == Piece::Type::Pawn) {
            Square captured = Square(move.to.col(), move.from.row());
            removed.add(captured);
        }
        Squares added = BB::bitboard(move.to);
        
        Square kingsPosition = position->kingPosition(side);
        if (move.from == kingsPosition) {
            kingsPosition = move.to;
            return Control::isControlling(position, kingsPosition, flip(side), removed, BB::bitboard(move.to));
        }
        
        Squares dangerLines = position->kingDangerLines();
        if (Control::isControllingByRookOrQueen(position, kingsPosition, flip(side), removed, added, dangerLines)) return true;
        if (Control::isControllingByBishopOrQueen(position, kingsPosition, flip(side), removed, added, dangerLines)) return true;
        if (Control::isControllingByKnight(position, kingsPosition, flip(side), removed, added)) return true;
        if (Control::isControllingByPawn(position, kingsPosition, flip(side), removed, added)) return true;
        if (Control::isControllingByKing(position, kingsPosition, flip(side), removed, added)) return true;
        
        return false;
    }
}  // namespace chessbox
