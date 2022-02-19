//
// LinesGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef LinesGenerator_h
#define LinesGenerator_h

namespace chessbox {
    
    // North
    template<int c, int r, Direction dir>
    struct BBLineGenerator {
        static constexpr int dc =
        (dir == NorthWest || dir == West || dir == SouthWest) ? -1 :
        ((dir == NorthEast || dir == East || dir == SouthEast) ? 1 : 0);
        
        static constexpr int dr =
        (dir == NorthEast || dir == North || dir == NorthWest) ? 1 :
        ((dir == SouthEast || dir == South || dir == SouthWest) ? -1 : 0);
        
        static constexpr BitBoard v  =
        BBSquareGenerator<c + 1 * dc, r + 1 * dr>::v |
        BBSquareGenerator<c + 2 * dc, r + 2 * dr>::v |
        BBSquareGenerator<c + 3 * dc, r + 3 * dr>::v |
        BBSquareGenerator<c + 4 * dc, r + 4 * dr>::v |
        BBSquareGenerator<c + 5 * dc, r + 5 * dr>::v |
        BBSquareGenerator<c + 6 * dc, r + 6 * dr>::v |
        BBSquareGenerator<c + 7 * dc, r + 7 * dr>::v
        ;
    };
    
#pragma mark - lines table
    
    template<int idx = 0, BitBoard ...D>
    struct BBLinesTableGenerator : BBLinesTableGenerator<idx + 1, D...,
    BBLineGenerator<idx%8, idx/8, North>::v,
    BBLineGenerator<idx%8, idx/8, NorthEast>::v,
    BBLineGenerator<idx%8, idx/8, East>::v,
    BBLineGenerator<idx%8, idx/8, SouthEast>::v,
    BBLineGenerator<idx%8, idx/8, South>::v,
    BBLineGenerator<idx%8, idx/8, SouthWest>::v,
    BBLineGenerator<idx%8, idx/8, West>::v,
    BBLineGenerator<idx%8, idx/8, NorthWest>::v  >
    {};
    
    template<BitBoard ...D>
    struct BBLinesTableGenerator<64, D...> {
        static constexpr std::array<BitBoard, 512> table = { D... };
    };
    
#pragma mark - rook lines table generator
    
    template<int idx = 0, BitBoard ...D>
    struct BBRookLinesTableGenerator : BBRookLinesTableGenerator<idx + 1, D...,
    BBLineGenerator<idx%8, idx/8, North>::v |
    BBLineGenerator<idx%8, idx/8, East>::v |
    BBLineGenerator<idx%8, idx/8, South>::v |
    BBLineGenerator<idx%8, idx/8, West>::v>
    {};
    
    template<BitBoard ...D>
    struct BBRookLinesTableGenerator<64, D...> {
        static constexpr std::array<BitBoard, 64> table = { D... };
    };
    
#pragma mark - bishop lines table generator
    
    template<int idx = 0, BitBoard ...D>
    struct BBBishopLinesTableGenerator : BBBishopLinesTableGenerator<idx + 1, D...,
    BBLineGenerator<idx%8, idx/8, NorthEast>::v |
    BBLineGenerator<idx%8, idx/8, SouthEast>::v |
    BBLineGenerator<idx%8, idx/8, SouthWest>::v |
    BBLineGenerator<idx%8, idx/8, NorthWest>::v>
    {};
    template<BitBoard ...D>
    struct BBBishopLinesTableGenerator<64, D...> {
        static constexpr std::array<BitBoard, 64> table = { D... };
    };

}

#endif /* LinesGenerator_h */
