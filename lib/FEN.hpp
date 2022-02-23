//
// FEN.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef FEN_hpp
#define FEN_hpp

#include "Position.hpp"

namespace chessbox {
    
    // Utility class to handle FENs.
    class FEN {
    public:
        
        // creates a position from the given FEN if possible.
        static Position * positionFromFEN(std::string FEN, const char **parseErrorAt = NULL);
        
        // Creates a FEN from the given position.
        // If `addMoveFields` is set to `false` move index and 50-move rule field is not added.
        static const std::string FENFromPosition(const Position *position, bool addMoveFields = true);
    };
    
} // namespace chessbox

#endif /* FEN_hpp */

