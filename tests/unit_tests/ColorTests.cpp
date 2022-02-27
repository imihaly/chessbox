//
// Created by Imre Mihaly on 2022.
//
// This code is licensed under MIT license (see LICENSE for more details).
//

#include "UnitTesting.hpp"
#include "Color.hpp"

TEST(Color, equality) {
    REQUIRE_EQ(Color::White, Color::White);
    REQUIRE_EQ(Color::Black, Color::Black);
}

TEST(Color, inequality) {
    REQUIRE_NE(Color::White, Color::Black);
    REQUIRE_NE(Color::Black, Color::White);
}

TEST(Color, other) {
    CHECK_TRUE(flip(Color::White) == Color::Black);
    CHECK_TRUE(flip(Color::Black) == Color::White);
}

