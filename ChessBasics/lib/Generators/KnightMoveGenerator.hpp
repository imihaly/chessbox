//
// KnightMoveGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef KnightMoveGenerator_h
#define KnightMoveGenerator_h

template<int c, int r>
struct BBKnightMoveGenerator {
    static const BitBoard v =
        BBSquareGenerator<c+1, r+2>::v |
        BBSquareGenerator<c+2, r+1>::v |
        BBSquareGenerator<c+2, r-1>::v |
        BBSquareGenerator<c+1, r-2>::v |
        BBSquareGenerator<c-1, r-2>::v |
        BBSquareGenerator<c-2, r-1>::v |
        BBSquareGenerator<c-2, r+1>::v |
        BBSquareGenerator<c-1, r+2>::v;
};


template<int idx = 0, BitBoard ...D>
struct BBKnightMovesTableGenerator : BBKnightMovesTableGenerator<idx + 1, D...,
    BBKnightMoveGenerator<idx%8, idx/8>::v>
{};

template<BitBoard ...D>
struct BBKnightMovesTableGenerator<64, D...> {
    static constexpr std::array<BitBoard, 64> table = { D... };
};



#endif /* KnightMoveGenerator_h */
