
#include "gfx/img.h"
#include "gfx/vec.h"
#include <fstream>

using namespace gfx;

void gfx::writePpmImage(const char *fn, 
        size_t width, size_t height, VecFunc<double, 2, 3> &cf) {

    std::ofstream file;
    file.open(fn);

    if (!file) {
        throw std::runtime_error("Could not open given file");
    }
    
    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;

    double dx = 2.0 / width;
    double dy = 2.0 / height;

    Vec2D coord;
    Vec3D color;

    coord[1] = 1.0 - (dy / 2.0);
    for (size_t r = 0; r < height; r++, coord[1] -= dy) {
        coord[0] = -1.0 + (dx / 2.0);
        for (size_t c = 0; c < width; c++, coord[0] += dx) {
            color = cf.apply(coord);

            for (size_t i = 0; i < 3; i++) {
                uint8_t colorComp = 255 * color[i];
                file.put(colorComp);
            }
        }
    }

    file.close();
}

