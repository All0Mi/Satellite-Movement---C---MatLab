#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

#include <cmath>
#include "../src/SatRange/SatRange.h"
#include "../src/Satellite/Satellite.h"

using point = Vector3<1,0>;
using axis = Vector3<1,0>;
using rVector = Vector3<1, 0>;

TEST_CASE("findRange") {
   point testPointA(3690, 1340, 5017);
   point testPointB(3568, -421, 5199);
   Satellite testSat(rVector(3800, -1500, 5800));
   testSat.setAxis(axis(0.2, -0.8, 0.4));

   std::array<int, 2> result = SatRange::findRange(testSat, testPointA, testPointB, 14);
   CHECK(result == std::array<int, 2>{-207, 129});
}

TEST_CASE("perpendicularPlane") {
    point testPoint(3690, 1340, 5017);
    CHECK(SatRange::perpendicularPlane(testPoint) == std::array<double, 4>{testPoint[0], testPoint[1], testPoint[2], rVector::norm(testPoint) * rVector::norm(testPoint)});
}

TEST_CASE("planeFactor") {
    point testPoint(3690, 1340, 5017);
    std::array<double, 4> testPlane = {1.0, 2.0, 3.0, 4.0} ;
    CHECK(SatRange::planeFactor(testPoint, testPlane) == testPlane[0] * testPoint[0] + testPlane[1] * testPoint[1] + testPlane[2] * testPoint[2]);
}