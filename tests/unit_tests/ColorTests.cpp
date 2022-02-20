//
// ColorTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//


#include "UnitTesting.hpp"
#include "Color.hpp"

TEST(Color, fail_test) {
    CHECK_TRUE(false);
}

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

//TEST(Color, description) {
//    CHECK_TRUE(Color::White.description() == "white");
//    CHECK_TRUE(Color::Black.description() == "black");
//    CHECK_TRUE(Color::Unknown.description() == "unknown");
//}

