//
// Gentest.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Gentest.hpp"
#include <vector>
#include <fstream>
#include "ChessBasics.hpp"
#include "Movedecoder.hpp"

std::vector<std::string> split(const std::string& s, char seperator)
{
   std::vector<std::string> output;

    std::string::size_type prev_pos = 0, pos = 0;

    while((pos = s.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( s.substr(prev_pos, pos-prev_pos) );

        output.push_back(substring);

        prev_pos = ++pos;
    }

    output.push_back(s.substr(prev_pos, pos-prev_pos)); // Last word

    return output;
}

void compare(Moves& moves1, Moves& moves2, Moves& inFirst, Moves& inSecond) {
    for(Move move: moves1) {
        if (moves2.contains(move)) continue;
        inFirst += move;
    }
    for(Move move: moves2) {
        if (moves1.contains(move)) continue;
        inSecond += move;
    }
}

Gentest::Gentest(std::string testfile): _testfile(testfile) {
    
}

bool Gentest::test() {    
    std::cout << "Running test: " << _testfile << ": " << std::endl;

    std::ifstream stream(_testfile);
    std::string startFen, movecount, moves, empty;
    int count = 0;
    Moves moveList;
    while(std::getline(stream, startFen) &&
          std::getline(stream, movecount) &&
          std::getline(stream, moves)
          )
    {
        Position *startPosition = FEN::positionFromFEN(startFen);
        if (!startPosition) {
            std::cout << "[🔴] " << "Failed to decode start pos in test " << (count + 1) << " from " << _testfile << std::endl;
            std::cout << "\t" << startFen << std::endl;
            return false;
        }
        
        moveList.clear();
        Movegen::allMoves(startPosition, moveList);
        
        std::vector<std::string> moveTexts = split(moves, ' ');
        Moves expectedMoves;
        for(std::string mt: moveTexts) {
            if(mt != "") {
                expectedMoves += decodeMove(mt);
            }
        }
        
        int expectedMovecount = stoi(movecount);
        if (moveList.size() != expectedMovecount) {
            std::cout << "[🔴] " << "Failed test " << (count + 1) << " from " << _testfile << std::endl;
            std::cout << "\tstart pos      : " << startFen << std::endl;
            std::cout << "\texpected count : " << expectedMovecount << std::endl;
            std::cout << "\tfound count    : " << moveList.size() << std::endl;
            std::cout << "\texpected: " << expectedMoves.description() << std::endl;
            std::cout << "\tfound: " << moveList.description() << std::endl;
            
            Moves inPlus, inMinus;
            compare(moveList, expectedMoves, inPlus, inMinus);
            std::cout << "\t +++: " << inPlus.description() << std::endl;
            std::cout << "\t ---:  " << inMinus.description() << std::endl;

            return false;
        }

        delete startPosition;

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
    std::cout << "[🟢] " << count << " gen tests from " << _testfile << std::endl;
    return true;
}
