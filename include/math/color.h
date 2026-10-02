#pragma once 

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linearToGamma(double linearComponent) {
    if (linearComponent > 0)
        return std::sqrt(linearComponent);

    return 0;
}

inline void writeColor(std::ostream& out, const color& pixelColor) {
    auto r = linearToGamma(pixelColor.x());
    auto g = linearToGamma(pixelColor.y());
    auto b = linearToGamma(pixelColor.z());

    static const interval intensity(0.000, 0.999);
    int rByte = int(256 * intensity.clamp(r));
    int gByte = int(256 * intensity.clamp(g));
    int bByte = int(256 * intensity.clamp(b));

    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}