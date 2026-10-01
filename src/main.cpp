#include "common.h"
#include "core/camera.h"
#include "geometry/hittable_list.h"
#include "geometry/sphere.h"

int main() {
    hittableList world;

    world.add(std::make_unique<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_unique<sphere>(point3(0,-100.5,-1), 100));

    camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400.0;

    cam.render(world);
}