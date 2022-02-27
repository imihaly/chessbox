//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
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
