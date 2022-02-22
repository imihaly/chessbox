//
// Movetest.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Movetest.hpp"
#include <vector>
#include <fstream>
#include "chessbox.hpp"
#include "Movedecoder.hpp"

Movetest::Movetest(std::string testfile): _testfile(testfile) {
    
}

bool Movetest::test() {
    std::cout << "Running test: " << _testfile << ": " << std::endl;
    std::ifstream stream(_testfile);
    std::string startFen, moveStr, endFen, empty;
    int count = 0;
    while(std::getline(stream, startFen) &&
          std::getline(stream, moveStr) &&
          std::getline(stream, endFen)
          )
    {

        Position *startPosition = FEN::positionFromFEN(startFen);
        if (!startPosition) {
            std::cout << "[🔴] " << "Failed to decode start pos in test " << (count + 1) << " from " << _testfile << std::endl;
            std::cout << "\t" << startFen << std::endl;
            return false;
        }

        Move move = decodeMove(moveStr);
//        if (!move) {
//            std::cout << "[🔴] " << "Failed to decode move in test " << (count + 1) << " from " << _testfile << std::endl;
//            std::cout << "\t" << startFen << std::endl;
//            std::cout << "\t" << moveStr << std::endl;
//            return false;
//        }

        Position *endPosition = NULL;
        endPosition = startPosition->positionWithMove(move);
        if (!endPosition) {
            std::cout << "[🔴] " << "Could not perform move in test " << (count + 1) << " from " << _testfile << std::endl;
            std::cout << "\tstart pos: " << startFen << std::endl;
            std::cout << "\tmove     : " << move.description() << std::endl;
            return false;
        }

        std::string regeneratedFen = FEN::FENFromPosition(endPosition);
        if(regeneratedFen != endFen) {
            std::cout << "[🔴] " << "Failed test " << (count + 1) << " from " << _testfile << std::endl;
            std::cout << "\t" << startFen << std::endl;
            std::cout << "\tstart pos: " << move.description() << std::endl;
            std::cout << "\tproduced : " << regeneratedFen << std::endl;
            std::cout << "\texpected : " << endFen << std::endl;
            return false;
        }
        
        delete startPosition;
        delete endPosition;

        if (count % 1000000 == 0) {
            std::cout << "\t" << (count / 1000000 + 1) << ": ";
        }

        count++;
        if (!std::getline(stream, empty)) break;
        
        if (count % 100000 == 0) {
            std::cout << "#";
        }
        if (count % 1000000 == 0) {
            std::cout << std::endl;
        }
    }
    
    std::cout << std::endl;
    std::cout << "[🟢] " << count << " move tests from " << _testfile << std::endl;
    return true;
}
