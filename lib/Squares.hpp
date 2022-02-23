//
// Squares.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Squares_hpp
#define Squares_hpp

#include "Square.hpp"
#include "BB.hpp"
#include "bitscan.hpp"

namespace chessbox {
    
    // Wrapper around a `BitBoard` to act like a standard container when representing a set of squares (as usually does).
    struct Squares {
        BitBoard v;
        
    public:
        Squares(): v(0) {}
        Squares(BitBoard v) : v(v) {}
        
    public:
        operator BitBoard() const {
            return v;
        }
        Squares operator +=(Squares other) {
            v += other.v;
            return *this;
        }
        Squares operator -=(Squares other) {
            v -= other.v;
            return *this;
        }
        Squares operator &=(Squares other) {
            v &= other.v;
            return *this;
        }
        Squares operator |=(Squares other) {
            v |= other.v;
            return *this;
        }
        Squares operator ^=(Squares other) {
            v ^= other.v;
            return *this;
        }
        Squares operator >>(int sv) const {
            return Squares(v >> sv) ;
        }
        Squares operator <<(int sv) const {
            return Squares(v >> sv) ;
        }
        bool operator==(Squares other) const {
            return  v == other.v;
        }
        bool operator!=(Squares other) const {
            return  v != other.v;
        }
        
        struct Iterator {
            BitBoard squares;
            
            Iterator(BitBoard squares): squares(squares) {
            }
            
            Square operator*() {
                return Square(ctz64(squares));
            }
            
            Iterator& operator++() {
                // switch off last bit
                squares &= (squares - 1);
                return *this;
            }
            
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            
            bool operator==(const Iterator& b) const {
                return squares == b.squares;
            }
            
            bool operator!=(const Iterator& b) const {
                return squares != b.squares;
            }
            
        };
        
        inline Iterator begin() const {
            return Iterator(v);
        }
        
        inline Iterator end() const {
            return  Iterator(0);
        }
        
        inline bool contains(const Square square) const {
            return (v >> (int)square) & 1;
        }
        
        inline void add(const Square square) {
            v |= (((uint64_t)1) << (int)square);
        }
        
        inline void remove(const Square square) {
            v &= ~(((uint64_t)1) << (int)square);
        }
        
        std::string description() const;
        
    };
    
} // namespace chessbox

#endif /* Squares_hpp */



