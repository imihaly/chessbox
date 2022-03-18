//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef SemanticError_hpp
#define SemanticError_hpp

#include <stdio.h>
#include "Error.hpp"

namespace chessbox {
    class SemanticError: public Error {
    public:
        SemanticError(std::string message): Error("SemanticErrorDomain"), _message(message) {
        }
        
    public:
        std::string message() const { return _message; }
        virtual std::string description() const;
        
    protected:
        virtual bool isEqual(const Error& error) const {
            const SemanticError& other = static_cast<const SemanticError&>(error);
            return Error::isEqual(other) && _message == other.message();
        }
        
    private:
        std::string _message;
    };
}

#endif /* SemanticError_hpp */
