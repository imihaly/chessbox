//
// StepsTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "Step.hpp"
#include "UnitTesting.hpp"

TEST(Step, multiply) {
    CHECK(Step(1, 1) * 3 == Step(3, 3));
    CHECK(Step(1, 1) * -3 == Step(-3, -3));
    CHECK(3 * Step(1, 1) == Step(3, 3));
}
