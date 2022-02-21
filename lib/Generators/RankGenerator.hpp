//
// RankGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef RankGenerator_h
#define RankGenerator_h

namespace chessbox {
    
    template<int r>
    struct BBRankGenerator {
        static const BitBoard v =
        BBSquareGenerator<0, r>::v |
        BBSquareGenerator<1, r>::v |
        BBSquareGenerator<2, r>::v |
        BBSquareGenerator<3, r>::v |
        BBSquareGenerator<4, r>::v |
        BBSquareGenerator<5, r>::v |
        BBSquareGenerator<6, r>::v |
        BBSquareGenerator<7, r>::v;
    };
    
} // namespace chessbox

#endif /* RankGenerator_h */
