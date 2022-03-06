//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//


#ifndef Result_hpp
#define Result_hpp

template<typename ValueType, typename ErrorType>
class Result {
public:
    Result(ValueType value) : _success(true), _value(value) {}
    Result(ErrorType error) : _success(false), _error(error) {}
    
public:
    operator bool() { return _success; };
    const ValueType& value() const { return _value; };
    const ErrorType& error() const { return _error; };

private:
    bool _success;
    ValueType _value;
    ErrorType _error;
};


#endif /* Result_h */
