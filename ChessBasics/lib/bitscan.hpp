//
// bitscan.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef bitscan_h
#define bitscan_h

#ifdef __GNUC__
    #define clz64(x) __builtin_clzl(x)
    #define ctz64(x) __builtin_ctzl(x)
#endif

#ifdef _MSC_VER
    #include <immintrin.h>
    #define clz64(x) _lzcnt_u64(x)
    #define ctz64(x) _tzcnt_u64(x)
#endif

#endif /* bitscan_h */
