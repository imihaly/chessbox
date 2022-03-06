//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "SemanticError.hpp"

namespace chessbox {
    std::string SemanticError::description() const {
        return "Semantic error: " + message();
    }
}
