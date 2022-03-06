//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "Error.hpp"

namespace chessbox {
    std::string Error::domain() const {
        return _domain;
    }
    
    int Error::errorCode() const {
        return _code;
        
    }
    
    std::string Error::description() const {
        return _domain + " ( " + std::to_string(_code) + " )";
    }
}
