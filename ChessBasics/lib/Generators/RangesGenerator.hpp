//
// RangesGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef RangesGenerator_h
#define RangesGenerator_h

template<int c1, int r1, int c2, int r2>
struct BBRangeGenerator {
    static const BitBoard v =
        (lineTable[(r1 * 8 + c1) * 8 + North] & lineTable[(r2 * 8 + c2) * 8 + South]) |
        (lineTable[(r1 * 8 + c1) * 8 + South] & lineTable[(r2 * 8 + c2) * 8 + North]) |
        (lineTable[(r1 * 8 + c1) * 8 + East] & lineTable[(r2 * 8 + c2) * 8 + West]) |
        (lineTable[(r1 * 8 + c1) * 8 + West] & lineTable[(r2 * 8 + c2) * 8 + East]) |
        (lineTable[(r1 * 8 + c1) * 8 + NorthEast] & lineTable[(r2 * 8 + c2) * 8 + SouthWest]) |
        (lineTable[(r1 * 8 + c1) * 8 + SouthWest] & lineTable[(r2 * 8 + c2) * 8 + NorthEast]) |
        (lineTable[(r1 * 8 + c1) * 8 + NorthWest] & lineTable[(r2 * 8 + c2) * 8 + SouthEast]) |
        (lineTable[(r1 * 8 + c1) * 8 + SouthEast] & lineTable[(r2 * 8 + c2) * 8 + NorthWest]);
};

template<int idx = 0, BitBoard ...D>
struct BBRangeTableGenerator : BBRangeTableGenerator<idx + 8, D...,
    BBRangeGenerator<((idx + 0)/64) % 8, ((idx + 0)/64) / 8, (idx + 0) % 8, ((idx + 0)%64) / 8>::v,
    BBRangeGenerator<((idx + 1)/64) % 8, ((idx + 1)/64) / 8, (idx + 1) % 8, ((idx + 1)%64) / 8>::v,
    BBRangeGenerator<((idx + 2)/64) % 8, ((idx + 2)/64) / 8, (idx + 2) % 8, ((idx + 2)%64) / 8>::v,
    BBRangeGenerator<((idx + 3)/64) % 8, ((idx + 3)/64) / 8, (idx + 3) % 8, ((idx + 3)%64) / 8>::v,
    BBRangeGenerator<((idx + 4)/64) % 8, ((idx + 4)/64) / 8, (idx + 4) % 8, ((idx + 4)%64) / 8>::v,
    BBRangeGenerator<((idx + 5)/64) % 8, ((idx + 5)/64) / 8, (idx + 5) % 8, ((idx + 5)%64) / 8>::v,
    BBRangeGenerator<((idx + 6)/64) % 8, ((idx + 6)/64) / 8, (idx + 6) % 8, ((idx + 6)%64) / 8>::v,
    BBRangeGenerator<((idx + 7)/64) % 8, ((idx + 7)/64) / 8, (idx + 7) % 8, ((idx + 7)%64) / 8>::v>
{};

template<BitBoard ...D>
struct BBRangeTableGenerator<64 * 64, D...> {
    static constexpr std::array<BitBoard, 64 * 64> table = { D... };
};

#endif /* RangesGenerator_h */
