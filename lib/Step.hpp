//
// Step.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Step_hpp
#define Step_hpp

#include <string>

namespace chessbox {
    
    // Represents a step on the chessboard.
    // Not strictly related to any piece's movement, just the travel distance measured in squares.
    struct Step {
        int dCol;
        int dRow;
        
        Step(int dCol, int dRow): dCol(dCol), dRow(dRow) {};
        
        bool operator==(const Step& other) const {
            return dCol == other.dCol && dRow == other.dRow;
        }
        
        bool operator!=(const Step& other) const {
            return dCol != other.dCol || dRow != other.dRow;
        }
        
        Step operator+(const Step& step) const {
            return Step(dCol + step.dCol, dRow + step.dRow);
        };
        
        Step operator-(const Step& step) const {
            return Step(dCol - step.dCol, dRow - step.dRow);
        };
        
        Step& operator+=(const Step& step) {
            dCol += step.dCol;
            dRow += step.dRow;
            return *this;
        };
        
        Step& operator-=(const Step& step) {
            dCol += step.dCol;
            dRow += step.dRow;
            return *this;
        };
        
        Step operator*(int s) {
            return Step(s*dCol, s*dRow);
        }
        
        friend Step operator*(int s, const Step& step) {
            return Step(s*step.dCol, s*step.dRow);
        }
        
        std::string description() const;
    };
    
} // namespace chessbox

#endif /* Step_hpp */

