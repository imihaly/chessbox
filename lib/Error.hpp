//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#ifndef Error_hpp
#define Error_hpp

#include <stdio.h>
#include <string>
#include <iostream>

namespace chessbox {
    class Error {
    public:
        Error(std::string domain = "GenericErrorDomain", int code = -1): _domain(domain), _code(code) {}
        Error(const Error& other) : _domain(other.domain()), _code(other.errorCode()) {}
        
    public:
        virtual std::string domain() const;
        virtual int errorCode() const;
        virtual std::string description() const;
        
    public:
        template<class T>
        bool isKindOf() const {
            return typeid(*this) == typeid(T);
        }
        
        bool operator==(const Error& other) const {
//            if (typeid(*this) != typeid(other)) {
//                std::cout << typeid(*this).name() << " " << typeid(other).name() << std::endl;
//            }
            return typeid(*this) == typeid(other) && isEqual(other);
        }

        bool operator!=(const Error& other) const {
            return typeid(*this) != typeid(other) || !isEqual(other);;
        }
        
    protected:
        virtual bool isEqual(const Error& other) const  {
            return _domain == other.domain() && _code == other.errorCode();
        }

    private:
        std::string _domain;
        int _code;
    };
}

#endif /* Error_hpp */
