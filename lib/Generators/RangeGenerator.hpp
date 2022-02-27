//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef RangesGenerator_h
#define RangesGenerator_h

namespace chessbox {
    
    template<int c1, int r1, int c2, int r2>
    struct BBRangeGenerator {
        static constexpr BitBoard v =
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + North] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + South]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + South] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + North]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + East] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + West]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + West] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + East]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + NorthEast] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + SouthWest]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + SouthWest] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + NorthEast]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + NorthWest] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + SouthEast]) |
        (BBLinesTableGenerator<>::table[(r1 * 8 + c1) * 8 + SouthEast] & BBLinesTableGenerator<>::table[(r2 * 8 + c2) * 8 + NorthWest]);
    };
    
    template<int from = 0, int idx = 0, BitBoard ...D>
    struct BBRangeTableGenerator : BBRangeTableGenerator<from, idx + 1, D...,
    BBRangeGenerator<from % 8, from / 8, idx % 8, idx / 8>::v> {};
    
    template<int from, BitBoard ...D>
    struct BBRangeTableGenerator<from, 64, D...> {
        static constexpr std::array<BitBoard, 64> v = { D... };
    };
    
} // namespace chessbox

#endif /* RangesGenerator_h */
