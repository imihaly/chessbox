//
// PawnCaptureGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef PawnCaptureGenerator_h
#define PawnCaptureGenerator_h

template<int c, int r>
struct BBPawnCaptureGenerator {
    static const BitBoard whiteControl = BBSquareGenerator<c-1, r+1>::v | BBSquareGenerator<c+1, r+1>::v;
    static const BitBoard blackControl = BBSquareGenerator<c-1, r-1>::v | BBSquareGenerator<c+1, r-1>::v;
};

template<int idx = 0, BitBoard ...D>
struct BBPawnCapturesTableGenerator : BBPawnCapturesTableGenerator<idx + 1, D...,
    BBPawnCaptureGenerator<idx%8, idx/8>::whiteControl,
    BBPawnCaptureGenerator<idx%8, idx/8>::blackControl>
{};

template<BitBoard ...D>
struct BBPawnCapturesTableGenerator<64, D...> {
    static constexpr std::array<BitBoard, 128> table = { D... };
};

#endif /* PawnCaptureGenerator_h */
