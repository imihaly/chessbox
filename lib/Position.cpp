//
// Position.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "Position.hpp"
#include "Control.hpp"
#include "Movecheck.hpp"
#include "BB.hpp"

#define assertm(exp, msg) assert(((void)msg, exp))

namespace chessbox {
    Position *Position::basePosition() {
        Position *position = new Position();
        position->_sideToMove = Color::White;
        position->_castlingRights[Color::White] = Kingside | Queenside;
        position->_castlingRights[Color::Black] = Kingside | Queenside;
        
        position->setPiece(Piece(Color::White, Piece::Type::Rook), Square::A1);
        position->setPiece(Piece(Color::White, Piece::Type::Knight), Square::B1);
        position->setPiece(Piece(Color::White, Piece::Type::Bishop), Square::C1);
        position->setPiece(Piece(Color::White, Piece::Type::Queen), Square::D1);
        position->setPiece(Piece(Color::White, Piece::Type::King), Square::E1);
        position->setPiece(Piece(Color::White, Piece::Type::Bishop), Square::F1);
        position->setPiece(Piece(Color::White, Piece::Type::Knight), Square::G1);
        position->setPiece(Piece(Color::White, Piece::Type::Rook), Square::H1);
        
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::A2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::B2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::C2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::D2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::E2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::F2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::G2);
        position->setPiece(Piece(Color::White, Piece::Type::Pawn), Square::H2);
        
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::A7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::B7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::C7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::D7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::E7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::F7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::G7);
        position->setPiece(Piece(Color::Black, Piece::Type::Pawn), Square::H7);
        
        position->setPiece(Piece(Color::Black, Piece::Type::Rook), Square::A8);
        position->setPiece(Piece(Color::Black, Piece::Type::Knight), Square::B8);
        position->setPiece(Piece(Color::Black, Piece::Type::Bishop), Square::C8);
        position->setPiece(Piece(Color::Black, Piece::Type::Queen), Square::D8);
        position->setPiece(Piece(Color::Black, Piece::Type::King), Square::E8);
        position->setPiece(Piece(Color::Black, Piece::Type::Bishop), Square::F8);
        position->setPiece(Piece(Color::Black, Piece::Type::Knight), Square::G8);
        position->setPiece(Piece(Color::Black, Piece::Type::Rook), Square::H8);
        
        return position;
    }
    
    Position::Position() : _sideToMove(Color::White),
    _enPassantSquare(Square::None),
    _controlledSquares{0, 0},
    _kingDangerLines(0),
    _squaresOccupiedByAny(0),
    _squaresOccupied{0, 0},
    _squaresOccupiedPerPieceType{{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}},
    _controlledSquaresNeedsRefresh(false)
    {
        _pieces = (Piece *)malloc(64 * sizeof(Piece));
        memset(_pieces, 0, 64 * sizeof(Piece));
        
        _halfMovesSinceLastPawnMoveOrCapture = 0;
        _moveIndex = 1;
        
        // castle availabilities
        _status = Ongoing;
        _castlingRights[Color::White] = 0;
        _castlingRights[Color::Black] = 0;
    }
    
    Position::Position(const Position& other) : _sideToMove(other.sideToMove()),
    _enPassantSquare(other.enPassantSquare()),
    _controlledSquares{0, 0},
    _kingDangerLines(0),
    _squaresOccupiedByAny(0),
    _squaresOccupied{0, 0},
    _squaresOccupiedPerPieceType{{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0}},
    _controlledSquaresNeedsRefresh(false),
    _kingPositions {other._kingPositions[0], other._kingPositions[1] }
    {
        _pieces = (Piece *)malloc(64 * sizeof(Piece));
        _pieces = (Piece *)memcpy(_pieces, other._pieces,64 * sizeof(Piece));
        _halfMovesSinceLastPawnMoveOrCapture = other._halfMovesSinceLastPawnMoveOrCapture;
        _moveIndex = other._moveIndex;
        
        for(int col = 0; col < 2; col++) {
            for(int pieceType = 0; pieceType < Piece::Type::Count; pieceType++) {
                _squaresOccupiedPerPieceType[col][pieceType] = other._squaresOccupiedPerPieceType[col][pieceType];
            }
        }
        
        // castle availabilities
        _status = other._status;
        _castlingRights[Color::White] = other._castlingRights[Color::White];
        _castlingRights[Color::Black] = other._castlingRights[Color::Black];
        
        _controlledSquaresNeedsRefresh = true;
        _squaresOccupied[Color::White] = other._squaresOccupied[Color::White];
        _squaresOccupied[Color::Black] = other._squaresOccupied[Color::Black];
        _squaresOccupiedByAny = other._squaresOccupiedByAny;
        _kingPositions[Color::White] = other._kingPositions[Color::White];
        _kingPositions[Color::Black] = other._kingPositions[Color::Black];
    }
    
    
    Position::~Position() {
        free(_pieces);
    }
    
    bool Position::makeMove(const Move move) {
        if (!Movecheck::isValidMove(this, move)) {
            return false;
        }
        performMove(move);
        return true;
    }
    
    Position *Position::positionWithMove(const Move move) const {
        if (!Movecheck::isValidMove(this, move)) {
            return NULL;
        }
        
        Position *ret = new Position(*this);
        if (!ret->makeMove(move)) {
            delete ret;
            return NULL;
            
        };
        
        return ret;
    }
    
    void Position::performMove(const Move move) {
        Square startSquare = move.from;
        const Piece& piece = pieceOnSquare(startSquare);
        bool capture = !isEmpty(move.to);
        Piece::Type pieceType = piece.type;
        
        if(pieceType == Piece::Type::Pawn) {
            performPawnMove(move);
        } else if(pieceType == Piece::Type::King) {
            performKingMove(move);
        } else if(pieceType == Piece::Type::Rook) {
            performRookMove(move);
        } else {
            movePiece(move);
        }
        
        if(pieceType != Piece::Type::Pawn && !capture) {
            _halfMovesSinceLastPawnMoveOrCapture++;
        } else {
            _halfMovesSinceLastPawnMoveOrCapture = 0;
        }
        
        if (_sideToMove == Color::Black) {
            _moveIndex++;
        }
        
        _sideToMove = flip(_sideToMove);
    }
    
    void Position::movePiece(const Move move) {
        Square startSquare = move.from;
        Square endSquare = move.to;
        
        const Piece piece = pieceOnSquare(startSquare);
        setPiece(Piece::NoPiece, startSquare);
        setPiece(piece, endSquare);
        
        if (endSquare == Square::A1) {
            setCastleQueenside(Color::White, false);
        }
        if (endSquare == Square::H1) {
            setCastleKingside(Color::White, false);
        }
        if (endSquare == Square::A8) {
            setCastleQueenside(Color::Black, false);
        }
        if (endSquare == Square::H8) {
            setCastleKingside(Color::Black, false);
        }
        
        // clear enPassantSquare
        setEnPassantSquare(Square::None);
    }
    
    void Position::performPawnMove(const Move move) {
        Color side = sideToMove();
        
        if (move.to == enPassantSquare()) {
            movePiece(move);
            Square captured = Square(move.to.col(), move.from.row());
            setPiece(Piece::NoPiece, captured);
            return;
        }
        
        // check if it is a jump, and set en-passant square
        int dr = move.to.row() - move.from.row();
        if (dr == 2 || dr == -2) {
            movePiece(move);
            Square enPassantSquare = Square(move.from.col(), move.from.row() + dr/2);
            setEnPassantSquare(enPassantSquare);
            return;
        }
        
        movePiece(move);
        
        // promote
        if (move.promotion != Piece::Type::None) {
            setPiece(Piece(side, move.promotion), move.to);
        }
    }
    
    void Position::performRookMove(const Move move) {
        if(sideToMove() == Color::White) {
            if (move.from == Square::H1) setCastleKingside(Color::White, false);
            if (move.from == Square::A1) setCastleQueenside(Color::White, false);
        } else {
            if (move.from == Square::H8) setCastleKingside(Color::Black, false);
            if (move.from == Square::A8) setCastleQueenside(Color::Black, false);
        }
        movePiece(move);
    }
    
    void Position::performKingMove(const Move move) {
        Color side = sideToMove();
        int r = move.from.row();
        
        if (canCastleKingside(side) && move.step() == Step(2, 0)) {
            // move the king
            const Piece piece = pieceOnSquare(move.from);
            setPiece(Piece::NoPiece, move.from);
            setPiece(piece, move.to);
            
            // move the rook
            Square rookFrom = Square(7, r);
            Square rookTo = Square(5, r);
            assert(pieceOnSquare(rookFrom) == Piece(side, Piece::Type::Rook));
            movePiece(Move(rookFrom, rookTo));
        } else if (canCastleQueenside(side) && move.step() == Step(-2, 0)) {
            // move the king
            const Piece piece = pieceOnSquare(move.from);
            setPiece(Piece::NoPiece, move.from);
            setPiece(piece, move.to);
            
            // move the rook
            Square rookFrom = Square(0, r);
            Square rookTo = Square(3, r);
            assert(pieceOnSquare(rookFrom) == Piece(side, Piece::Type::Rook));
            movePiece(Move(rookFrom, rookTo));
        } else {
            movePiece(move);
        }
        setCastleQueenside(side, false);
        setCastleKingside(side, false);
    }
    
#pragma mark - square control
    
    const Squares& Position::squaresControlledBy(Color side) const {
        if (_controlledSquaresNeedsRefresh) {
            _controlledSquares[Color::White] = Control::squaresControlled(this, Color::White);
            _controlledSquares[Color::Black] = Control::squaresControlled(this, Color::Black);
            _controlledSquaresNeedsRefresh = false;
        }
        
        return _controlledSquares[side];
    }
    
    std::ostream& operator<<(std::ostream& os, const Position& position) {
        os << position.description();
        return os;
    }
    
#pragma mark - properties
    
    void Position::setSideToMove(Color side) {
        _sideToMove = side;
        
    }
    
    void Position::setPiece(Piece piece, const Square square) {
        _pieces[(int)square] = piece;
        if(piece == Piece::NoPiece) {
            _squaresOccupied[Color::White].remove(square);
            _squaresOccupied[Color::Black].remove(square);
            _squaresOccupiedByAny.remove(square);
            for(int pieceType = 0; pieceType < Piece::Type::Count; pieceType++) {
                _squaresOccupiedPerPieceType[Color::White][pieceType].remove(square);
                _squaresOccupiedPerPieceType[Color::Black][pieceType].remove(square);
            }
        } else {
            _squaresOccupied[piece.color].add(square);
            _squaresOccupiedByAny.add(square);
            _squaresOccupiedPerPieceType[piece.color][piece.type].add(square);
        }
        
        _controlledSquaresNeedsRefresh = true;
        
        if (piece.type == Piece::Type::King) {
            _kingPositions[piece.color] = square;
        } else if(square == _kingPositions[piece.color]) {
            _kingPositions[piece.color] = Square::None;
        }
        
        _kingDangerLinesMessed = true;
    }
    
    std::string Position::description() const {
        std::string ret;
        for(int row = 7; row >= 0; row--) {
            for(int col = 0; col < 8; col++) {
                ret += pieceOnSquare(Square(col, row)).description();
            }
            ret += '\n';
        }
        return ret;
    }
    
    void Position::setEnPassantSquare(const Square square) {
        _enPassantSquare = square;
    }
    
    bool Position::canCastleKingside(Color side) const {
        return _castlingRights[side] & Kingside;
    }
    
    bool Position::canCastleQueenside(Color side) const {
        return _castlingRights[side] & Queenside;
    }
    
    void Position::setCastleKingside(Color side, bool set) {
        if(set) {
            _castlingRights[side] |= Kingside;
        } else {
            _castlingRights[side] &= ~Kingside;
        }
    }
    
    void Position::setCastleQueenside(Color side, bool set) {
        if(set) {
            _castlingRights[side] |= Queenside;
        } else {
            _castlingRights[side] &= ~Queenside;
        }
    }
    
    Square Position::kingPosition(Color color) const {
        return _kingPositions[color];
    }
    
    int Position::halfMovesSinceLastPawnMoveOrCapture() const {
        return _halfMovesSinceLastPawnMoveOrCapture;
    }
    
    void Position::setHalfMovesSinceLastPawnMoveOrCapture(int value) {
        _halfMovesSinceLastPawnMoveOrCapture = value;
    }
    
    int Position::moveIndex() const {
        return _moveIndex;
    }
    
    void Position::setMoveIndex(int value) {
        _moveIndex = value;
    }
    
    const Squares& Position::kingDangerLines() const{
        if (_kingDangerLinesMessed) {
            Color side = sideToMove();
            Color other = flip(side);
            
            _kingDangerLines = 0;
            Square kingsSquare = _kingPositions[side];
            Squares rooksBishopsAndQueens = (squaresOccupied(other, Piece::Type::Rook) | squaresOccupied(other, Piece::Type::Bishop) | squaresOccupied(other, Piece::Type::Queen)) & BB::lines(kingsSquare);
            for(Squares::Iterator it = rooksBishopsAndQueens.begin(); it != rooksBishopsAndQueens.end(); it++) {
                Direction dir = BB::dir(kingsSquare, *it);
                _kingDangerLines |= BB::line(kingsSquare, dir);
            }
            
            _kingDangerLinesMessed = false;
        }
        
        return _kingDangerLines;
    }

}
