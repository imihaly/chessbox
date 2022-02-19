//
// DirectionsGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef DirectionsGenerator_h
#define DirectionsGenerator_h

template<int c1, int r1, int c2, int r2>
struct BBDirectionGenerator {
    static const Direction v =
    c1 == c2 && r1 == r2 ? Direction::Any :
    c1 == c2 && r1 > r2 ? Direction::South :
    c1 == c2 && r1 < r2 ? Direction::North :
    r1 == r2 && c1 > c2 ? Direction::West :
    r1 == r2 && c1 < c2 ? Direction::East :
    (r2 - r1) == (c2 - c1) && (r2 - r1) < 0 ? Direction::SouthWest :
    (r2 - r1) == (c2 - c1) && (r2 - r1) > 0 ? Direction::NorthEast :
    (r2 - r1) == (c1 - c2) && (r2 - r1) < 0 ? Direction::SouthEast :
    (r2 - r1) == (c1 - c2) && (r2 - r1) > 0 ? Direction::NorthWest :
    Direction::Unknown;
};

template<int idx = 0, Direction ...D>
struct BBDirectionsTableGenerator : BBDirectionsTableGenerator<idx + 8, D...,
    BBDirectionGenerator<((idx + 0)/64) % 8, ((idx + 0)/64) / 8, (idx + 0) % 8, ((idx + 0)%64) / 8>::v,
    BBDirectionGenerator<((idx + 1)/64) % 8, ((idx + 1)/64) / 8, (idx + 1) % 8, ((idx + 1)%64) / 8>::v,
    BBDirectionGenerator<((idx + 2)/64) % 8, ((idx + 2)/64) / 8, (idx + 2) % 8, ((idx + 2)%64) / 8>::v,
    BBDirectionGenerator<((idx + 3)/64) % 8, ((idx + 3)/64) / 8, (idx + 3) % 8, ((idx + 3)%64) / 8>::v,
    BBDirectionGenerator<((idx + 4)/64) % 8, ((idx + 4)/64) / 8, (idx + 4) % 8, ((idx + 4)%64) / 8>::v,
    BBDirectionGenerator<((idx + 5)/64) % 8, ((idx + 5)/64) / 8, (idx + 5) % 8, ((idx + 5)%64) / 8>::v,
    BBDirectionGenerator<((idx + 6)/64) % 8, ((idx + 6)/64) / 8, (idx + 6) % 8, ((idx + 6)%64) / 8>::v,
    BBDirectionGenerator<((idx + 7)/64) % 8, ((idx + 7)/64) / 8, (idx + 7) % 8, ((idx + 7)%64) / 8>::v> {};

template<Direction ...D>
struct BBDirectionsTableGenerator<64 * 64, D...> {
    static constexpr std::array<Direction, 64 * 64> table = { D... };
};

template<int from = 0, int idx = 0, Direction ...D>
struct BBDirectionsSubTableGenerator : BBDirectionsSubTableGenerator<from, idx + 1, D...,
BBDirectionGenerator<from % 8, from / 8, idx % 8, idx / 8>::v> {};

template<int from, Direction ...D>
struct BBDirectionsSubTableGenerator<from, 64, D...> {
    static constexpr std::array<Direction, 64> v = { D... };
};

#endif /* DirectionsGenerator_h */
