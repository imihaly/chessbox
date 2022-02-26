//
// Position.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Position_hpp
#define Position_hpp

#include "Color.hpp"
#include "Square.hpp"
#include "Squares.hpp"
#include "Piece.hpp"
#include "Move.hpp"
#include "Direction.hpp"


namespace chessbox {
    
    // sides
    typedef enum {
        Kingside = 1,
        Queenside = 2
    } Side;
    
    class Position {
        
    public:
        static Position *basePosition();
        Position();
        Position(const Position& other);
        ~Position();
        
    public:
        const Color sideToMove() const {
            return _sideToMove;
        };
        void setSideToMove(Color side);
        
        const Piece& pieceOnSquare(const Square square) const {
            return _pieces[(int)square];
        };
        void setPiece(Piece piece, const Square square);
        
        bool isEmpty(const Square square) const {
            return pieceOnSquare(square).type == Piece::Type::None;
        };
        
        Square enPassantSquare() const {
            return  _enPassantSquare;;
        };
        void setEnPassantSquare(const Square square);
        
        int halfMovesSinceLastPawnMoveOrCapture() const;
        void setHalfMovesSinceLastPawnMoveOrCapture(int value);
        
        int moveIndex() const;
        void setMoveIndex(int value);
        
    public:
        
        bool canCastleKingside(Color side) const;
        bool canCastleQueenside(Color side) const;
        void setCastleKingside(Color side, bool set);
        void setCastleQueenside(Color side, bool set);
        Square kingPosition(Color color) const;
        
    public:
        bool hasMoves() const;
        bool isKingChecked() const;
        bool isMate() const;
        bool isStaleMate() const;
        
    public:
        const Squares& squaresControlledBy(Color side) const;
        
    public:
        // Performs the move by modifying the position.
        // Checks that the move is valid and returns false if it isn't.
        bool makeMove(const Move move);
        
        // Creates a new position by performing the given move.
        // Chacks that the move is possible and returns NULL if it isn't.
        Position *positionWithMove(const Move move) const;
        
        // Just performs the move and updates the move-related properties.
        // en-passant square, castling rights, 50-move rule
        //
        // Warning: doesn't checks if the move is valid, so might result in an invaid state if used carelessly.
        void performMove(const Move move);
        
    private:
        void performPawnMove(const Move move);
        void performRookMove(const Move move);
        void performKingMove(const Move move);
        
        // Mindlessly moves the piece and clears the en-passant square.
        void movePiece(const Move move);
        
    private:
        // these members are changed only in `squaresControlledBy` and in `setPiece` in order to avoid recalculating the controlled squares too often.
        mutable Squares _controlledSquares[2];
        mutable bool _controlledSquaresNeedsRefresh;
        
    private:
        Squares _squaresOccupiedByAny;
        Squares _squaresOccupied[2];
        Squares _squaresOccupiedPerPieceType[2][Piece::Type::Count];
        
    public:
        const Squares squaresOccupied() const {return _squaresOccupiedByAny; };
        const Squares& squaresOccupied(Color side)  const { return _squaresOccupied[side]; };
        const Squares& squaresOccupied(Color side, Piece::Type type) const { return _squaresOccupiedPerPieceType[side][type]; };
        
    private:
        Piece* _pieces;
        Color _sideToMove;
        
        // en-passant
        Square _enPassantSquare;
        
        // castle
        int _castlingRights[2];
        
        // 50-move rule
        int _halfMovesSinceLastPawnMoveOrCapture;
        
        int _moveIndex;
        
        Square _kingPositions[2];
        
        // lines with potential attacker on it
        mutable Squares _kingDangerLines;
        mutable bool _kingDangerLinesMessed;
        
    public:
        const Squares& kingDangerLines() const;
    };
    
} // namespace chessbox

#endif /* Position_hpp */

