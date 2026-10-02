#pragma once

#include "common.h"
#include "geometry/hittable.h"
#include "math/vec3.h"
#include "math/color.h"
#include "math/ray.h"
#include "math/interval.h"

class camera {
public:
    camera();

    float aspectRatio;
    int imageWidth;
    int samplesPerPixel;
    
    void render(const hittable& world, std::ostream& out = std::cout);

private:
    int imageHeight;
    // scale factor for sum of pixel samples
    double pixelSamplesScale;
    // the exact 3d position where the camera eye is placed
    point3 cameraCenter;
    // the 3d location of the very first pixel at the top left of the screen
    point3 pixel00Loc;
    // the 3d distance between each pixel moving horizontally to the right
    vec3 pixelDeltaU;
    // the 3d distance between each pixel moving vertically downward
    vec3 pixelDeltaV;

    void initialize();
    // shoots a single ray into the world and figures out what color to bring back
    color rayColor(const ray& r, const hittable& world);
    // returns a vector to a random point inside the pixel square [-.5, -.5]-[+.5, +.5]
    vec3 sampleSquare() const;
    // returns a ray originating from the origin and directed at random points around the pixel (i, j)
    ray getRay(int i, int j) const;
};