# Chessbox

A simple C++ chess library.

# Features
1. Create a chess position:
`Position *position = Position::basePosition(); // Creates the initial starting position.`
`Position *position = new Position(); // creates an empty position`
2. Query various properties of the position:
`Color side = position->sideToMove(); // Who's turn it is?`
`Piece piece = position->pieceOnSquare(Square::E2);`
`if (position->canCastleKingside(Color::White) { ... }`
`position->isStalemate();`
`position->isMate();`
3. Validate a move:
`Movecheck::isValidMove(position, move);`
4. Make a move:
`position->makeMove(move);`
5. Generate valid moves:
`Moves allMoves = Movegen::allMoves(position);`
6. Create chess position from FEN:
`Position *position = FEN::positionFromFEN("7K/8/5k2/8/8/8/8/8 w - - 0 1");`
7. Create FEN from a chess position:
`std::string FEN = FEN::FENfromPosition(position);`


