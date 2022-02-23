//
// Step.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Step.hpp"

#include <sstream>

namespace chessbox {
    std::string Step::description() const {
        std::ostringstream s;
        s << "(" << dCol << "," << dRow << ")";
        return s.str();
    }
}  // namespace chessbox
