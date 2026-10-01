#include "core/camera.h"

camera::camera() {
    aspectRatio = 1.0;
    imageWidth = 100;
}

void camera::initialize() {
    // figure out how tall the image should be based on the width and ratio
    imageHeight = int(imageWidth / aspectRatio);
    // force the image to be at least one pixel tall so we do not divide by zero later
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // the distance from the camera eye to the virtual screen
    auto focalLength = 1.0;
    // the physical height of the virtual screen in our 3d world
    auto viewportHeight = 2.0;
    // the physical width of the virtual screen scaled to match our image ratio
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    
    // a right handed coordinate system means x goes right and y goes up
    // this means looking forward into the screen is the negative z direction
    // we place our camera directly at the center of the universe
    cameraCenter = point3(0, 0, 0);

    // a vector spanning the width of the screen moving horizontally to the right
    auto viewportU = vec3(viewportWidth, 0, 0);
    // a vector spanning the height of the screen moving vertically down
    // it goes down because image scanlines are drawn from top to bottom
    auto viewportV = vec3(0, -viewportHeight, 0);

    // chop the screen vectors into tiny steps to find the distance between individual pixels
    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    // find the exact top left corner of the virtual screen in 3d space
    // we start at the camera then move forward into the screen by the focal length
    // then we move left by half the width and up by half the height
    auto viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - (viewportU / 2.0) - (viewportV / 2.0);
    
    // shift the starting point slightly so our rays go perfectly through the center of the first pixel
    pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

void camera::render(const hittable& world) {
    initialize();

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;

        for (int i = 0; i < imageWidth; i++) {
            // calculate the exact 3d target for this specific pixel
            auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            // create a direction arrow pointing from the camera toward the pixel
            auto rayDirection = pixelCenter - cameraCenter;
            // build the actual ray starting at the camera and moving along the direction
            ray r(cameraCenter, rayDirection);

            // figure out what color this ray hits out in the world
            color pixelColor = rayColor(r, world);
            // output that final color to our image file
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}

color camera::rayColor(const ray& r, const hittable& world) {
    hitRecord rec;
    
    // check if the ray hits any object between zero and infinity
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    
    // the ray missed everything so we draw the sky background instead
    vec3 unitDir = unitVector(r.getDirection());
    // scale the vertical y direction from a range to a simple zero to one value
    float a = 0.5 * (unitDir.y() + 1.0);
    // blend between white at the bottom and blue at the top based on the y height
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}