//
// Gentest.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Gentest_hpp
#define Gentest_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>

class Gentest {
public:
    Gentest(std::string testfile);
    bool test();
    
private:
    std::string _testfile;
};

#endif /* Gentest_hpp */
