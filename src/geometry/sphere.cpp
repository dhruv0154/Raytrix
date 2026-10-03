#include "geometry/sphere.h"

#include <cmath>

sphere::sphere(const point3& center, double radius, std::shared_ptr<material> mat) 
    : center(center), radius(std::fmax(0.0, radius)), mat(mat) {}

// ray intersection test
bool sphere::hit(const ray& r, interval rayT, hitRecord& rec) const {
    const vec3 rayDir = r.getDirection();
    const vec3 oc = center - r.getOrigin();
    double a = rayDir.lengthSquared();
    double h = dot(rayDir, oc);
    double c = oc.lengthSquared() - (radius * radius);

    double discriminant = h * h - a * c;
    if (discriminant < 0) return false;
    
    // find the nearest root that lies in our range
    double sqrtd = std::sqrt(discriminant);
    double root = (h - sqrtd) / a;
    if (root <= rayT.min || root >= rayT.max) {
        root = (h + sqrtd) / a;
        if (root <= rayT.min || root >= rayT.max) return false;
    }

    // store the result in ref of rec
    rec.t = root;
    rec.p = r.at(rec.t);
    
    // length of a vector at any pt on a sphere is
    // equal to the radius of the sphere
    vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    rec.mat = mat;
    
    return true;
}