#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#include "math/color.h"
#include "math/vec3.h"
#include "math/ray.h"

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}