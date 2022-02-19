//
// FileGenerator.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef FileGenerator_h
#define FileGenerator_h

template<int c>
struct BBFileGenerator {
    static const BitBoard v =
        BBSquareGenerator<c, 0>::v |
        BBSquareGenerator<c, 1>::v |
        BBSquareGenerator<c, 2>::v |
        BBSquareGenerator<c, 3>::v |
        BBSquareGenerator<c, 4>::v |
        BBSquareGenerator<c, 5>::v |
        BBSquareGenerator<c, 6>::v |
        BBSquareGenerator<c, 7>::v;
};

#endif /* FileGenerator_h */
