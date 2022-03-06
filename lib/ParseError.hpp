//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef ParseError_hpp
#define ParseError_hpp

#include <stdio.h>
#include <string>
#include "Error.hpp"

namespace chessbox {
    class ParseError: public Error {
    public:
        ParseError(std::string file, int line, int pos): Error("ParseErrorDomain"), _file(file), _line(line), _pos(pos) {
        }
        
        ParseError(int pos = -1): Error("ParseErrorDomain"), _file(""), _line(0), _pos(pos) {
        }

    public:
        std::string file() const { return _file; }
        int line() const { return _line; }
        int pos() const { return _pos; }
        virtual std::string description() const;
        
    protected:
        virtual bool isEqual(const Error& error) const {
            const ParseError& other = static_cast<const ParseError&>(error);
            return Error::isEqual(other) && _file == other.file() && _line == other.line() && _pos == other.pos();
        }
        
    private:
        std::string _file;
        int _line;
        int _pos;
    };
}

#endif /* ParseError_hpp */
