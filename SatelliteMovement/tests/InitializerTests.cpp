#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

#include "../src/Initializer/Initializer.h"

using rVector = Vector3<1,0>;
using point = Vector3<1,0>;

TEST_CASE("initializer generateSetOfValidPoints")
{
    point testPointA(3690, 1340, 5017);
    point testPointB(3658, -421, 5199);
    CHECK_NOTHROW(Initializer::generateSetOfValidPoints(100, 2, testPointA, testPointB));
}

TEST_CASE("initializer initSatellites")
{
    std::vector<rVector> v = {rVector(1,2,3)};
    point testPointA(3690, 1340, 5017);
    point testPointB(3658, -421, 5199);
    std::vector<Satellite> s = Initializer::initSatellites(v, testPointA, testPointB, 14);
    CHECK(s[0].getPoint() == rVector(1,2,3));
}