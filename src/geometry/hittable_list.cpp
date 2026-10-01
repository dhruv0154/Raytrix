#include "geometry/hittable_list.h"

hittableList::hittableList() {}

hittableList::hittableList(std::unique_ptr<hittable> object) { 
    add(std::move(object)); 
}

void hittableList::clear() { 
    objects.clear(); 
}

void hittableList::add(std::unique_ptr<hittable> object) {
    objects.push_back(std::move(object));
}

// ray intersection test against all objects
bool hittableList::hit(const ray& r, interval rayT, hitRecord& rec) const {
    hitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = rayT.max;

    for (const auto& object : objects) {
        if (object->hit(r, interval(rayT.min, closestSoFar), tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}