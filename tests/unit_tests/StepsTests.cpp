//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "Step.hpp"
#include "UnitTesting.hpp"

TEST(Step, multiply) {
    CHECK_TRUE(Step(1, 1) * 3 == Step(3, 3));
    CHECK_TRUE(Step(1, 1) * -3 == Step(-3, -3));
    CHECK_TRUE(3 * Step(1, 1) == Step(3, 3));
}
