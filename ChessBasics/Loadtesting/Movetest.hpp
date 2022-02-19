//
// Movetest.hpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#ifndef Movetest_hpp
#define Movetest_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>

class Movetest {
public:
    Movetest(std::string testfile);
    bool test();
    
private:
    std::string _testfile;
};



#endif /* Movetest_hpp */
