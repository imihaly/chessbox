//
// PawnMoveGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef PawnMoveGenerator_h
#define PawnMoveGenerator_h

namespace chessbox {
    
    template<int c, int r>
    struct BBPawnMoveGenerator {
        static const BitBoard whiteMove = BBSquareGenerator<c, r+1>::v;
        static const BitBoard blackMove = BBSquareGenerator<c, r-1>::v;
    };
    
    template<int c>
    struct BBPawnMoveGenerator<c, 1> {
        static const BitBoard whiteMove = BBSquareGenerator<c, 2>::v|BBSquareGenerator<c, 3>::v;
        static const BitBoard blackMove = BBSquareGenerator<c, 0>::v;
    };
    
    template<int c>
    struct BBPawnMoveGenerator<c, 6> {
        static const BitBoard whiteMove = BBSquareGenerator<c, 7>::v;
        static const BitBoard blackMove = BBSquareGenerator<c, 5>::v|BBSquareGenerator<c, 4>::v;
    };
    
    // building table
    
    template<int idx = 0, BitBoard ...D>
    struct BBPawnMovesTableGenerator : BBPawnMovesTableGenerator<idx + 1, D..., BBPawnMoveGenerator<idx%8, idx/8>::whiteMove, BBPawnMoveGenerator<idx%8, idx/8>::blackMove>
    {};
    
    template<BitBoard ...D>
    struct BBPawnMovesTableGenerator<64, D...> {
        static constexpr std::array<BitBoard, 128> table = { D... };
    };
    
} // namespace chessbox

#endif /* PawnMoveGenerator_h */
