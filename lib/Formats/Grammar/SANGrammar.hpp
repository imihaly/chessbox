//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

// Standard Algebraic Notation
//<SAN move descriptor piece moves>   ::= <Piece symbol>[<from file>|<from rank>|<from square>]['x']<to square>
//<SAN move descriptor pawn captures> ::= <from file>[<from rank>] 'x' <to square>[<promoted to>]
//<SAN move descriptor pawn push>     ::= <to square>[<promoted to>]

#define LOG(x)  // std::cout << x << std::endl;

STATE(Initial, { })
    SWITCH(isPieceSymbol, PieceMove,        {  pieceType = pieceTypeFromSymbol(c); } )
    SWITCH(isFileSymbol,  PawnMove,         {  coordinates.push_back(c); /* fileFromSymbol(c); */ } )
    SWITCH(isO,           CastleO,          {  } )
    SWITCH(isZero,        Castle0,          {  } )
    FAIL(-1)

// piece move
STATE(PieceMove, { LOG("PieceMove") })
    SWITCH(isFileSymbol,  PieceFile,        {  coordinates.push_back(c); /* fileFromSymbol(c); */ } )  // may be fromFile, fromSquare's file, or ToSquare's file
    SWITCH(isRankSymbol,  PieceFrom,        {  coordinates.push_back(c);  /* rankFromSymbol(c); */ } )
    PASS(PieceFrom,                         { } )

STATE(PieceFile, { LOG("PieceFile") })
    SWITCH(isRankSymbol,  PieceFileRank,    {  coordinates.push_back(c);  /* rankFromSymbol(c); */ } ) // may be from Square's rank or toSquare's rank
    PASS(PieceFrom,                         { } )
    FAIL(-2)

STATE(PieceFileRank, { LOG("PieceFileRank") })
    SWITCH(isCaptureSymbol, PieceWaitingForTarget,      { isCapture = true; } ) // we know that prev square was a specifier, capture flag should be set
    SWITCH(isFileSymbol,    PieceFromFile,  {  coordinates.push_back(c); /* fileFromSymbol(c); */ } ) // we know that prev square was a specifier
    PASS(PostMove,                          { })                           // we know that prev square was a to-square
    FAIL(-3)

STATE(PieceFrom, { LOG("PieceFrom") })
    SWITCH(isCaptureSymbol, PieceWaitingForTarget,      { isCapture = true; } )
    PASS(PieceWaitingForTarget,             { })

STATE(PieceWaitingForTarget, { LOG("PieceWaitingForTarget") })
    SWITCH(isFileSymbol,  PieceFromFile,    {  coordinates.push_back(c);  /* fileFromSymbol(c); */ } )
    FAIL(-4)

STATE(PieceFromFile, { LOG("PieceFromFile") })
    SWITCH(isRankSymbol,  PostMove,         {  coordinates.push_back(c);  /* rankFromSymbol(c); */ } )
    FAIL(-5)

// Pawn move
STATE(PawnMove, { LOG("PawnMove") })
    SWITCH(isRankSymbol,  PawnSquare,       {  coordinates.push_back(c);  /* rankFromSymbol(c); */ } )
    SWITCH(isCaptureSymbol,  PawnFrom,      { isCapture = true; } ) // set capture
    FAIL(-6)

STATE(PawnSquare, { LOG("PawnSquare") })
    SWITCH(isCaptureSymbol,  PawnFrom,      { coordinates.push_back(c);  /*rankFromSymbol(c); */} )
    PASS(Promotion,                         { } )

STATE(PawnFrom, { LOG("PawnFrom") })
    SWITCH(isFileSymbol,  PawnFromFile,     {  coordinates.push_back(c);  /* fileFromSymbol(c); */ } )
    FAIL(-7)

STATE(PawnFromFile, { LOG("PawnFromFile") })
    SWITCH(isRankSymbol,  Promotion,         {  coordinates.push_back(c); /* rankFromSymbol(c); */ } )
    FAIL(-8)

STATE(Promotion, {LOG("Promotion")})
    SWITCH(isPieceSymbol, PostMove,         { promotionType = pieceTypeFromSymbol(c); })
    PASS(PostMove, {})

// O-O-O || O-O
STATE(CastleO, { LOG("O") })
    SWITCH(isMinus, CastleO_,               { } )
    FAIL(-9)

STATE(CastleO_, { LOG("O-") })
    SWITCH(isO, CastleO_O,                  { } )
    FAIL(-10)

STATE(CastleO_O, { LOG("O-O") })
    SWITCH(isMinus, CastleO_O_,             { } )
    PASS(PostMove,                          { setShortCastle(); } )

STATE(CastleO_O_, { LOG("O-O-") })
    SWITCH(isO, PostMove,                   { setLongCastle(); } )
    FAIL(-11)

// 0-0-0 || 0-0
STATE(Castle0, { LOG("0") })
    SWITCH(isMinus, Castle0_,               { } )
    FAIL(-12)

STATE(Castle0_, { LOG("0-") })
    SWITCH(isZero, Castle0_0,               { } )
    FAIL(-13)

STATE(Castle0_0, { LOG("0-0") })
    SWITCH(isMinus, Castle0_0_,             { } )
    PASS(PostMove,                          { setShortCastle(); } )

STATE(Castle0_0_, { LOG("0-0-") })
    SWITCH(isZero, PostMove,                { setLongCastle(); } )
    FAIL(-14)

STATE(PostMove, { LOG("checkOrMate") })
    SWITCH(isCheckSymbol, shouldEnd,        { isCheck = true; } )
    SWITCH(isCheckmateSymbol, shouldEnd,    { isMate = true; } )
    PASS(shouldEnd,                         { } )

STATE(shouldEnd, { LOG("shouldEnd") })
    SWITCH(isEndSymbol, End,                { })
    FAIL(-15)

STATE(End, { })
