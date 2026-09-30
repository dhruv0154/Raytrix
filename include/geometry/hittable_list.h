#pragma once

#include "hittable.h"
#include <vector>

class hittableList : public hittable {
public:
    hittableList() {}
    hittableList(std::unique_ptr<hittable> object) { add(std::move(object)); }

    void clear() { objects.clear(); }

    void add(std::unique_ptr<hittable> object) {
        objects.push_back(std::move(object));
    }

    bool hit(const ray& r, double rayTmin, double rayTmax, hitRecord& rec) const override {
        hitRecord tempRec;
        bool hitAnything = false;
        double closestSoFar = rayTmax;

        for (const auto& object : objects) {
            if (object -> hit(r, rayTmin, closestSoFar, tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec.t;
                rec = tempRec;
            }
        }

        return hitAnything;
    }

private:
    std::vector<std::unique_ptr<hittable>> objects;
};