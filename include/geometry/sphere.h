#pragma once

#include "hittable.h"

class material;

class sphere : public hittable {
public:
    sphere(const point3& center, double radius, std::shared_ptr<material> mat);
    
    // ray intersection test
    bool hit(const ray& r, interval rayT, hitRecord& rec) const override;

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};