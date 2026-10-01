#pragma once

#include "hittable.h"
#include <vector>
#include <memory>

class hittableList : public hittable {
public:
    hittableList();
    hittableList(std::unique_ptr<hittable> object);

    // list management
    void clear();
    void add(std::unique_ptr<hittable> object);

    // ray intersection test
    bool hit(const ray& r, interval rayT, hitRecord& rec) const override;

private:
    std::vector<std::unique_ptr<hittable>> objects;
};