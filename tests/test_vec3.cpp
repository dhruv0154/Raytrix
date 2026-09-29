#include "math/vec3.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <sstream>

TEST_CASE("vec3 initializes to zero or specified values", "[vec3]") {
    vec3 defaultVec;
    REQUIRE(defaultVec[0] == 0.0);
    REQUIRE(defaultVec[1] == 0.0);
    REQUIRE(defaultVec[2] == 0.0);

    vec3 paramVec(1.0, 2.0, 3.0);
    REQUIRE(paramVec.x() == 1.0);
    REQUIRE(paramVec.y() == 2.0);
    REQUIRE(paramVec.z() == 3.0);
}

TEST_CASE("vec3 array indexing supports read and write", "[vec3]") {
    vec3 v;
    v[0] = 4.5;
    v[1] = 5.5;
    v[2] = 6.5;

    REQUIRE(v[0] == 4.5);
    REQUIRE(v[1] == 5.5);
    REQUIRE(v[2] == 6.5);
}

TEST_CASE("vec3 arithmetic operators function correctly", "[vec3]") {
    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(4.0, 5.0, 6.0);

    // Addition
    vec3 sum = v1 + v2;
    REQUIRE(sum[0] == 5.0);
    REQUIRE(sum[1] == 7.0);
    REQUIRE(sum[2] == 9.0);

    // Subtraction
    vec3 diff = v2 - v1;
    REQUIRE(diff[0] == 3.0);
    REQUIRE(diff[1] == 3.0);
    REQUIRE(diff[2] == 3.0);

    // Negation
    vec3 neg = -v1;
    REQUIRE(neg[0] == -1.0);
    REQUIRE(neg[1] == -2.0);
    REQUIRE(neg[2] == -3.0);
}

TEST_CASE("vec3 scalar multiplication and division work", "[vec3]") {
    vec3 v(2.0, 4.0, 6.0);

    vec3 scaled = v * 2.0;
    REQUIRE(scaled[0] == 4.0);
    REQUIRE(scaled[1] == 8.0);
    REQUIRE(scaled[2] == 12.0);

    vec3 scaledCommutative = 3.0 * v;
    REQUIRE(scaledCommutative[0] == 6.0);
    REQUIRE(scaledCommutative[1] == 12.0);
    REQUIRE(scaledCommutative[2] == 18.0);

    vec3 divided = v / 2.0;
    REQUIRE(divided[0] == 1.0);
    REQUIRE(divided[1] == 2.0);
    REQUIRE(divided[2] == 3.0);
}

TEST_CASE("vec3 compound assignment operators modify in-place", "[vec3]") {
    vec3 v(1.0, 2.0, 3.0);
    
    v += vec3(1.0, 1.0, 1.0);
    REQUIRE(v[0] == 2.0);

    v *= 3.0;
    REQUIRE(v[0] == 6.0);
    REQUIRE(v[1] == 9.0);
    REQUIRE(v[2] == 12.0);
}

TEST_CASE("vec3 geometric and vector math utilities operate accurately", "[vec3]") {
    vec3 u(1.0, 2.0, 3.0);
    vec3 v(4.0, 5.0, 6.0);

    // Component wise multiplication (Color blending)
    vec3 prod = u * v;
    REQUIRE(prod[0] == 4.0);
    REQUIRE(prod[1] == 10.0);
    REQUIRE(prod[2] == 18.0);

    // Dot product: (1*4 + 2*5 + 3*6) = 4 + 10 + 18 = 32
    REQUIRE(dot(u, v) == 32.0);

    // Length and length squared
    vec3 axis(0.0, 3.0, 4.0);
    REQUIRE(axis.lengthSquared() == 25.0);
    REQUIRE(axis.length() == 5.0);

    // Unit vector normalization check using floating point matchers
    vec3 unit = unitVector(axis);
    REQUIRE_THAT(unit.y(), Catch::Matchers::WithinRel(0.6, 0.0001));
    REQUIRE_THAT(unit.z(), Catch::Matchers::WithinRel(0.8, 0.0001));
}

TEST_CASE("vec3 stream insertion operator formats correctly for PPM", "[vec3]") {
    vec3 v(255, 128, 0);
    std::ostringstream out;
    out << v;
    REQUIRE(out.str() == "255 128 0");
}