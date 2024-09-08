
#pragma once

#include <cstdlib>
#include <exception>
#include <fstream>
#include <stdexcept>

#include "gfx/vec.h"

namespace gfx {
void writePpmImage(const char *fn, 
        size_t width, size_t height, VecFunc<double, 2, 3> &cf);
}
