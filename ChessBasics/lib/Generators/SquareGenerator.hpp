//
// SquareGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef SquareGenerator_h
#define SquareGenerator_h

template <int col, int row>
struct BBSquareGenerator {
    static constexpr BitBoard v = (col < 0 || col > 7 || row < 0 || row > 7) ? 0 : BitBoard(1) << (row * 8 + col);
};

template<int idx = 0, BitBoard ...D>
struct BBSquaresTableGenerator : BBSquaresTableGenerator<idx + 1, D..., BBSquareGenerator<idx%8, idx/8>::v>
{};

template<BitBoard ...D>
struct BBSquaresTableGenerator<64, D...> {
    static constexpr std::array<BitBoard, 64> table = { D... };
};


#endif /* SquareGenerator_h */
