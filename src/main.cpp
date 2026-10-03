#include "common.h"
#include "core/camera.h"
#include "geometry/hittable_list.h"
#include "core/material.h"
#include "geometry/sphere.h"

#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

int main() {
    hittableList world;
    auto materialGround = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<metal>(color(0.8, 0.8, 0.8));
    auto materialRight = std::make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(std::make_unique<sphere>(point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_unique<sphere>(point3(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.add(std::make_unique<sphere>(point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_unique<sphere>(point3(1.0, 0.0, -1.0), 0.5, materialRight));

    camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400.0;
    cam.samplesPerPixel = 100;
    cam.maxDepth = 50;

    #ifndef ROOT_DIR
    #define ROOT_DIR "." 
    #endif

    std::string folderName = std::string(ROOT_DIR) + "/renders";
    std::filesystem::create_directory(folderName);

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << folderName << "/render_" << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S") << ".ppm";
    std::string filename = ss.str();

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Failed to create output file!\n";
        return 1;
    }

    cam.render(world, outFile);
}