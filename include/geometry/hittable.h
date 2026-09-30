#pragma once

#include "ray.h"

struct hitRecord {
    point3 p;
    vec3 normal;
    double t;
    bool frontFace;

    void setFaceNormal(const ray& r, const vec3& outwardNormal) {
        // sets the hit record normal vector.
        // the parameter `outward_normal` is assumed to have unit length.

        // if both the ray and the normal points in the opposite dir.
        // the dot product will be negative and hence the ray is outside the surface.
        frontFace = dot(r.getDirection(), outwardNormal) < 0;
        // if it's the front face, keep the normal pointing outward. 
        // if it's the back face (inside), flip the normal so it points inward (against the ray).
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;
    // check if the ray hit the object
    virtual bool hit(const ray& r, double rayTmin, double rayTmax, hitRecord& rec) const = 0;
};