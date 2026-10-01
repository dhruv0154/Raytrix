#include "math/ray.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Ray initializes origin and direction correctly", "[ray]") {
    point3 origin(1.0, 2.0, 3.0);
    vec3 direction(4.0, 5.0, 6.0);
    ray r(origin, direction);

    REQUIRE(r.getOrigin() == origin);
    REQUIRE(r.getDirection() == direction);
}

TEST_CASE("Ray at(t) computes correct 3D positions", "[ray]") {
    point3 origin(0.0, 0.0, 0.0);
    vec3 direction(1.0, 2.0, 3.0);
    ray r(origin, direction);

    // Test t = 0 (Exactly at the camera/origin)
    REQUIRE(r.at(0.0) == point3(0.0, 0.0, 0.0));

    // Test positive t (In front of the camera)
    REQUIRE(r.at(1.0) == point3(1.0, 2.0, 3.0));
    REQUIRE(r.at(2.5) == point3(2.5, 5.0, 7.5));

    // Test negative t (Behind the camera)
    REQUIRE(r.at(-1.0) == point3(-1.0, -2.0, -3.0));
}