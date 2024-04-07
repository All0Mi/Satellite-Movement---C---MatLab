#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

#include "../src/Vector3/Vector3.h"
#include "../src/Satellite/Satellite.h"

using point = Vector3<1,0>;
using axis = Vector3<1,0>;
using rVector = Vector3<1, 0>;

TEST_CASE("randomRotationAxis") {
    point testPoint = { 1.0, 2.0, 3.0};
    CHECK_NOTHROW(Satellite::randomRotationAxis(testPoint));
}