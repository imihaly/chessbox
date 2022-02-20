//
// main.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include <iostream>
#include "Movetest.hpp"
#include "Gentest.hpp"

int main(int argc, const char * argv[]) {
    
    Movetest("/Users/ildi/Imre/Projects.new/ChessBasics/Loadtesting/Resources/Loadtest_002.movetest").test();
    Gentest("/Users/ildi/Imre/Projects.new/ChessBasics/Loadtesting/Resources/Loadtest_001.gentest").test();
    
    return 0;
}
