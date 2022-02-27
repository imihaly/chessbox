//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef PawnCaptureGenerator_h
#define PawnCaptureGenerator_h

namespace chessbox {
    
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
    
} // namespace chessbox

#endif /* PawnCaptureGenerator_h */
