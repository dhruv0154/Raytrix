#include "common.h"
#include "core/camera.h"
#include "geometry/hittable_list.h"
#include "geometry/sphere.h"

#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

int main() {
    hittableList world;
    world.add(std::make_unique<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_unique<sphere>(point3(0,-100.5,-1), 100));

    camera cam;
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 400.0;
    cam.samplesPerPixel = 100;

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