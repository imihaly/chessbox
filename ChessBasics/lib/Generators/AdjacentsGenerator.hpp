//
// AdjacentsGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef AdjacentsGenerator_h
#define AdjacentsGenerator_h

template<int col, int row, Direction dir>
struct BBAdjacentsGenerator {
    static const int dc =
        (dir == NorthWest || dir == West || dir == SouthWest) ? -1 :
        ((dir == NorthEast || dir == East || dir == SouthEast) ? 1 : 0);
    
    static const int dr =
        (dir == NorthEast || dir == North || dir == NorthWest) ? 1 :
        ((dir == SouthEast || dir == South || dir == SouthWest) ? -1 : 0);

    static const BitBoard v    = (col < 0 || col > 7 || row < 0 || row > 7) ? 0 : BBSquareGenerator<col + dc, row + dr>::v;
};


#pragma mark - adjacents per direction table

template<int idx = 0, BitBoard ...D>
struct BBAdjacentsPerDirectionTableGenerator : BBAdjacentsPerDirectionTableGenerator<idx + 1, D...,
    BBAdjacentsGenerator<idx%8, idx/8, North>::v,
    BBAdjacentsGenerator<idx%8, idx/8, NorthEast>::v,
    BBAdjacentsGenerator<idx%8, idx/8, East>::v,
    BBAdjacentsGenerator<idx%8, idx/8, SouthEast>::v,
    BBAdjacentsGenerator<idx%8, idx/8, South>::v,
    BBAdjacentsGenerator<idx%8, idx/8, SouthWest>::v,
    BBAdjacentsGenerator<idx%8, idx/8, West>::v,
    BBAdjacentsGenerator<idx%8, idx/8, NorthWest>::v>
{};

template<BitBoard ...D>
struct BBAdjacentsPerDirectionTableGenerator<64, D...> {
    static constexpr std::array<BitBoard, 512> table = { D... };
};

#pragma mark - adjacents table generator

template<int idx = 0, BitBoard ...D>
struct BBAdjacentsTableGenerator : BBAdjacentsTableGenerator<idx + 1, D...,
    BBAdjacentsGenerator<idx%8, idx/8, North>::v |
    BBAdjacentsGenerator<idx%8, idx/8, NorthEast>::v |
    BBAdjacentsGenerator<idx%8, idx/8, East>::v |
    BBAdjacentsGenerator<idx%8, idx/8, SouthEast>::v |
    BBAdjacentsGenerator<idx%8, idx/8, South>::v |
    BBAdjacentsGenerator<idx%8, idx/8, SouthWest>::v |
    BBAdjacentsGenerator<idx%8, idx/8, West>::v |
    BBAdjacentsGenerator<idx%8, idx/8, NorthWest>::v>
{};

template<BitBoard ...D>
struct BBAdjacentsTableGenerator<64, D...> {
    static constexpr std::array<BitBoard, 64> table = { D... };
};



#endif /* AdjacentsGenerator_h */
