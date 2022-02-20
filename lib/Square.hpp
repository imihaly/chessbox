//
// Square.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include "deps.h"
#include "Step.hpp"

namespace chessbox {
    struct Square {
        static const Square A1, B1, C1, D1, E1, F1, G1, H1;
        static const Square A2, B2, C2, D2, E2, F2, G2, H2;
        static const Square A3, B3, C3, D3, E3, F3, G3, H3;
        static const Square A4, B4, C4, D4, E4, F4, G4, H4;
        static const Square A5, B5, C5, D5, E5, F5, G5, H5;
        static const Square A6, B6, C6, D6, E6, F6, G6, H6;
        static const Square A7, B7, C7, D7, E7, F7, G7, H7;
        static const Square A8, B8, C8, D8, E8, F8, G8, H8;
        static const Square None;
        
        int_fast8_t v;
        Square(int col, int row) {
            if (col < 0 || col > 7 || row < 0 || row > 7) {
                // invalid
                v = -1;
            } else {
                v = row * 8 + col;
            }
        }
        
        explicit Square(int_fast8_t v=0): v(v) {}
        
        explicit operator int_fast8_t() const {
            return v;
        }
        
        explicit operator int() const {
            return v;
        }
        
        inline int row() const {
            return v >> 3;
        }
        
        inline int col() const {
            return v % 8;
        }
        
        inline Step operator-(const Square from) const {
            return Step(col() - from.col(), row() - from.row());
        };
        
        inline bool operator==(const Square other) const {
            return v == other.v;
        }
        
        inline bool operator!=(const Square other) const {
            return v != other.v;
        }
        
        inline bool isValid() {
            return v >= 0;
        };
        
        std::string description() const;
    };
    
    inline Square operator+(const Square square, const Step& step) {
        int c = square.col() + step.dCol;
        int r = square.row() + step.dRow;
        
        return Square(c, r);
    };
    
    inline Square operator-(const Square square, const Step& step) {
        int c = square.col() - step.dCol;
        int r = square.row() - step.dRow;
        
        return Square(c, r);
    };
    
}
#endif /* Square_hpp */



