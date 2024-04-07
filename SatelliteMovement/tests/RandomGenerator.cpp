#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

#include "../src/RandomGenerator/RandomGenerator.h"

TEST_CASE("random gen default constructor")
{
    CHECK_NOTHROW(RandomGenerator{});
}

TEST_CASE("random gen double")
{
    RandomGenerator gen{};
    CHECK_NOTHROW(gen.randDouble(0, 1000));
}

TEST_CASE("random gen int")
{
    RandomGenerator gen{};
    CHECK_NOTHROW(gen.randInt(0, 1000));
}

TEST_CASE("random default gen int")
{
    RandomGenerator gen{};
    CHECK_NOTHROW(gen.randInt());
}

TEST_CASE("random default double")
{
    RandomGenerator gen{};
    CHECK_NOTHROW(gen.randDouble());
}