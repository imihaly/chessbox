# Chessbox

A simple C++ chess library.

## Building and testing the lib:
- Configure: `cmake -B build`
- Build the static lib: `make -C build cbox`
- Run unit tests: `make -C build unit_tests`
- Run performance tests: `make -C perf_tests`

## Features
### 1. Create a chess position:
- Standard starting position: `Position *position = Position::basePosition();`
- An empty position: `Position *position = new Position();`
- Custom position from a FEN: `Position *position = FEN::positionFromFEN("7K/8/5k2/8/8/8/8/8 w - - 0 1");`

### 2. Query various properties of the position:
- Side to move: `Color side = position->sideToMove();`
- The piece on a square: `Piece piece = position->pieceOnSquare(Square::E2);`
- Castling rights: `position->canCastleKingside(Color::White)`
- Check if the position is stalemate: `position->isStalemate();`
- Check if the position is a mate: `position->isMate();`

### 3. Make a move:
```
position->makeMove(move);
```

### 4. Validate a move:
```
Movecheck::isValidMove(position, move);
```

### 5. Generate valid moves:
```
Moves allMoves = Movegen::allMoves(position);
```

### 6. Create FEN from a chess position:
```
std::string FEN = FEN::FENfromPosition(position);
```

### Further features:
- Move validation functions are implemented in `Movecheck` class.
- Square-control related functions are impleemnted in `Control` class.
- Move genereation functions are in `Movegen` class.
- FEN-handling is placed in `FEN` class.

