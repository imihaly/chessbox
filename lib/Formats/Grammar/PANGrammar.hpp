//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

// Pure Algebraic Notation
// <from><to>[promotion]

#define LOG(x) // std::cout << x << std::endl;

STATE(Initial, { })
SWITCH(isFileSymbol,  FromSquareRow,    {  startFile = fileFromSymbol(c); } )
FAIL(-1)

STATE(FromSquareRow, { LOG("from.row") })
SWITCH(isRankSymbol,  ToSquareCol,    {  startRank = rankFromSymbol(c); } )
FAIL(-2)

STATE(ToSquareCol, { LOG("to.col") })
SWITCH(isFileSymbol,  ToSquareRow,     { endFile = fileFromSymbol(c); } )
FAIL(-3)

STATE(ToSquareRow, { LOG("to.row") })
SWITCH(isRankSymbol,  Promotion,       { endRank = rankFromSymbol(c); } )
FAIL(-4)

STATE(Promotion, { LOG("promotion") })
SWITCH(isPieceSymbol, shouldEnd,     {  promotionType = pieceTypeFromSymbol(c); } )
PASS(shouldEnd,                        {  } )

STATE(shouldEnd, { LOG("shouldEnd") })
SWITCH(isEndSymbol, End,               {  })

STATE(End, { })
