//
// Step.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Step.hpp"

namespace chessbox {
    std::string Step::description() const {
        std::ostringstream s;
        s << "(" << dCol << "," << dRow << ")";
        return s.str();
    }
    
    std::ostream& operator<<(std::ostream& os, const Step& step) {
        os << step.description();
        return os;
    }
}
