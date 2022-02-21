//
// DirectionsGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef DirectionsGenerator_h
#define DirectionsGenerator_h

namespace chessbox {
    
    // Utility template struct to produce a constant direction for a pair of squares( from = (c1, r1), to = (c2, r2) ).
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
    
    // Utility template struct generating a table containing direections to each 64 squares from the square `from`
    template<int from = 0, int idx = 0, Direction ...D>
    struct BBDirectionTableGenerator : BBDirectionTableGenerator<from, idx + 1, D...,
        BBDirectionGenerator<from % 8, from / 8, idx % 8, idx / 8>::v> {};
    
    template<int from, Direction ...D>
    struct BBDirectionTableGenerator<from, 64, D...> {
        static constexpr std::array<Direction, 64> v = { D... };
    };
    
} // namespace chessbox

#endif /* DirectionsGenerator_h */
