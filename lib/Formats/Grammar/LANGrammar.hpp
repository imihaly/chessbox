//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

// Long Algebraic Notation
//    <LAN move descriptor piece moves> ::= <Piece symbol><from square>['-'|'x']<to square>
//    <LAN move descriptor pawn moves>  ::= <from square>['-'|'x']<to square>[<promoted to>]
//    <Piece symbol> ::= 'N' | 'B' | 'R' | 'Q' | 'K'


#define LOG(x) // std::cout << x << std::endl;

STATE(Initial, { })
    SWITCH(isPieceSymbol, FromSquareCol,    {  pieceType = pieceTypeFromSymbol(c); } )
    SWITCH(isFileSymbol,  FromSquareRow,    {  startFile = fileFromSymbol(c); } )
    SWITCH(isO,           CastleO,          {  } )
    SWITCH(isZero,        Castle0,          {  } )
    FAIL(-1)

STATE(FromSquareCol, { LOG("from.col") })
    SWITCH(isFileSymbol,  FromSquareRow,    {  startFile = fileFromSymbol(c); } )
    FAIL(-2)

STATE(FromSquareRow, { LOG("from.row") })
    SWITCH(isRankSymbol,  MoveOrCapture,    {  startRank = rankFromSymbol(c); } )
    FAIL(-3)

STATE(MoveOrCapture, { LOG("-|x") })
    SWITCH(isMoveSymbol,  ToSquareCol,      {  isCapture = false; } )
    SWITCH(isCaptureSymbol,  ToSquareCol,   {  isCapture = true; } )
    FAIL(-4)

STATE(ToSquareCol, { LOG("to.col") })
    SWITCH(isFileSymbol,  ToSquareRow,     { endFile = fileFromSymbol(c); } )
    FAIL(-5)

STATE(ToSquareRow, { LOG("to.row") })
    SWITCH(isRankSymbol,  Promotion,       { endRank = rankFromSymbol(c); } )
    FAIL(-6)

STATE(Promotion, { LOG("promotion") })
    SWITCH(isPieceSymbol, CheckOrMate,     {  promotionType = pieceTypeFromSymbol(c); } )
    PASS(CheckOrMate,                      {  } )

    // O-O-O || O-O
STATE(CastleO, { LOG("O") })
    SWITCH(isMinus, CastleO_,              {  } )
    FAIL(-7)

STATE(CastleO_, { LOG("O-") })
    SWITCH(isO, CastleO_O,                 {  } )
    FAIL(-8)

STATE(CastleO_O, { LOG("O-O") })
    SWITCH(isMinus, CastleO_O_,            {  } )
    PASS(CheckOrMate,                      {  setShortCastle(); } )

STATE(CastleO_O_, { LOG("O-O-") })
    SWITCH(isO, CheckOrMate,               {  setLongCastle(); } )
    FAIL(-9)

    // 0-0-0 || 0-0
STATE(Castle0, { LOG("0") })
    SWITCH(isMinus, Castle0_,              {  } )
    FAIL(-10)
    
STATE(Castle0_, { LOG("0-") })
    SWITCH(isZero, Castle0_0,              { } )
    FAIL(-11)
    
STATE(Castle0_0, { LOG("0-0") })
    SWITCH(isMinus, Castle0_0_,            {  LOG(c) } )
    PASS(CheckOrMate,                      {  setShortCastle(); } )
    
STATE(Castle0_0_, { LOG("0-0-") })
    SWITCH(isZero, CheckOrMate,            {  setLongCastle(); } )
    FAIL(-12)

STATE(CheckOrMate, { LOG("checkOrMate") })
    SWITCH(isCheckSymbol, shouldEnd,       {  isCheck = true; } )
    SWITCH(isCheckmateSymbol, shouldEnd,   {  isMate = true; } )
    PASS(shouldEnd,                        {  } )

STATE(shouldEnd, { LOG("shouldEnd") })
    SWITCH(isEndSymbol, End,               { })
    
STATE(End, { })
