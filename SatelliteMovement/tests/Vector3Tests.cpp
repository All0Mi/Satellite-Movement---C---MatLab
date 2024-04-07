//
// Created by rafaln on 22.12.23.
//
#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN

#include "../src/Vector3/Vector3.h"

using vector = Vector3<0,0>;

TEST_CASE("vector default constructor")
{
    CHECK_NOTHROW(vector());
}

TEST_CASE("vector param constructor")
{
    CHECK_NOTHROW(vector(1,1,1));
}

TEST_CASE("vector == operator")
{
    vector v = vector(1,1,1);
    CHECK(v == vector(1,1,1));
}

TEST_CASE("vector + operator")
{
    vector a = vector(1,1,1);
    vector b = vector(1,2,3);
    CHECK((a + b) == vector(2,3,4));
}

TEST_CASE("vector - operator")
{
    vector a = vector(1,1,1);
    vector b = vector(1,2,3);
    CHECK((a - b) == vector(0,-1,-2));
}

TEST_CASE("vector / operator")
{
    vector a = vector(1,1,1);
    CHECK((a / 2) == vector(0.5,0.5,0.5));
}

TEST_CASE("vector [] operator")
{
    vector v = vector(1,2,3);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
}

TEST_CASE("vector * operator")
{
    vector v = vector(1,2,3);
    CHECK(v*2 == vector(2,4,6));
}

TEST_CASE("vector norm")
{
    vector v = vector(5,0,0);
    CHECK(vector::norm(v) == 5);
    v = vector(0,2,0);
    CHECK(vector::norm(v) == 2);
    v = vector(0,0,3);
    CHECK(vector::norm(v) == 3);
}

TEST_CASE("vector areParallel")
{
    vector a = vector(1,1,1);
    vector b = vector(1,1,1);
    CHECK(vector::areParallel(a,b));
}

TEST_CASE("vector areParallel 2")
{
    vector a = vector(1,1,1);
    vector b = vector(1,1,2);
    CHECK(!vector::areParallel(a,b));
}


TEST_CASE("vector crossProduct")
{
    vector a = vector(1,3,4);
    vector b = vector(3,2,8);
    CHECK(vector::crossProduct(a, b) == vector(16,4,-7));
}

TEST_CASE("vector rotation")
{
    vector p(1,2,3);
    vector axis(0, 0, 1);
    vector result = vector::rotateAroundAxis(p, axis, M_PI/2);
    CHECK((result.abs() - vector(-2,1,3).abs()) < 0.01);

    axis = vector(0,1,0);
    result = vector::rotateAroundAxis(p, axis, M_PI/2);
    CHECK((result.abs() - vector(3,2,-1).abs()) < 0.01);

    axis = vector(1,0,0);
    result = vector::rotateAroundAxis(p, axis, M_PI/2);
    CHECK((result.abs() - vector(1,-3,2).abs()) < 0.01);
}
