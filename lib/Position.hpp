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
        friend class Movecheck;
        friend class Movegen;
        friend class Control;

    public:
        
        // Returns a new position set to the standard starting position.
        static Position *basePosition();
        
        // Cretaes an empty position.
        Position();
        
        // Constructs a copy of the given position.
        Position(const Position& other);
                
        ~Position();
        
        
    public:
        
        // MARK: - getters and setters for basic position properties
        
        // getter and setter for the moving side.
        const Color sideToMove() const {
            return _sideToMove;
        };
        void setSideToMove(Color side);
        
        // getter and setter for pieces.
        const Piece& pieceOnSquare(const Square square) const {
            return _pieces[(int)square];
        };
        void setPiece(Piece piece, const Square square);

        // getter and setter for the en-passant square.
        Square enPassantSquare() const {
            return  _enPassantSquare;;
        };
        void setEnPassantSquare(const Square square);
        
        // getter and setter for 50-move rule property.
        int halfMovesSinceLastPawnMoveOrCapture() const;
        void setHalfMovesSinceLastPawnMoveOrCapture(int value);
        
        // getter and setter for move index.
        int moveIndex() const;
        void setMoveIndex(int value);

        // getters and setters for castling rights
        bool canCastleKingside(Color side) const;
        void setCastleKingside(Color side, bool set);

        bool canCastleQueenside(Color side) const;
        void setCastleQueenside(Color side, bool set);
        
    public:
        // MARK: - derived properties

        // Checks if a square is empty.
        bool isEmpty(const Square square) const {
            return pieceOnSquare(square).type == Piece::Type::None;
        };
        
        // Returns the king's position.
        // If there are more kings of teh same color in the position, it will return the position of one of them but it is undefined which one will it be.
        Square kingPosition(Color color) const;
        
        // Returns if there are any legal moves in the given position.
        bool hasMoves() const;
        
        // Returns if the king of the moving side is in check.
        bool isKingChecked() const;
        
        // Returns if the moving side is mated in the given position.
        bool isMate() const;
        
        // Returns if the current position is stalemate.
        bool isStaleMate() const;
        
        // Returns the collection of squares controlled by the given side.
        const Squares& squaresControlledBy(Color side) const;
        
        // Returns the collection of squares occupied by any piece.
        const Squares& squaresOccupied() const {return _squaresOccupied; };
        
        // Returns the collection of squares occupied by any of the given side's pieces.
        const Squares& squaresOccupied(Color side)  const { return _squaresOccupiedPerSide[side]; };

        // Returns the collection of squares occupied by a piece of the given side and type.
        const Squares& squaresOccupied(Color side, Piece::Type type) const { return _squaresOccupiedPerPieceType[side][type]; };

    public:
        // Performs the move by modifying the position.
        // Checks that the move is valid and returns false if it isn't.
        bool makeMove(const Move move);
        
        // Creates a new position by performing the given move.
        // Checks that the move is possible and returns NULL if it isn't.
        Position *positionWithMove(const Move move) const;
        
        // Just performs the move and updates the move-related properties.
        // en-passant square, castling rights, 50-move rule
        //
        // Warning: doesn't checks if the move is valid, so might result in an invaid state if used carelessly.
        void performMove(const Move move);
        
    private:
        // Performs a pawn move and updates the en-passant square.
        void performPawnMove(const Move move);
        
        // Performs a rook move and updates the castling rights.
        void performRookMove(const Move move);

        // Performs a king move and updates the castling rights.
        void performKingMove(const Move move);
        
        // Mindlessly moves the piece and clears the en-passant square.
        void movePiece(const Move move);
                
        // Squares on any of the lines running from king's position to any direction and containing a potential attacker on that line.
        const Squares& kingDangerLines() const;
        
    private:
        // array of pieces.
        Piece* _pieces;
        
        // The moving side.
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
        
        // these members are changed only in `squaresControlledBy` and in `setPiece` in order to avoid recalculating the controlled squares too often.
        mutable Squares _controlledSquares[2];
        mutable bool _controlledSquaresNeedsRefresh;
        
        Squares _squaresOccupied;
        Squares _squaresOccupiedPerSide[2];
        Squares _squaresOccupiedPerPieceType[2][Piece::Type::Count];
        
    };
    
} // namespace chessbox

#endif /* Position_hpp */

