
#include "gfx/img.h"
#include "gfx/vec.h"
#include <stdexcept>

using namespace gfx;

class MyVF : public VecFunc<double, 2, 3> {
public:
    MyVF() : VecFunc<double, 2, 3>() {}
    virtual Vec<double, 3> apply(const Vec<double, 2> &v) override {
        double x = (v[0] + 1.0) / 2.0;
        double y = (v[1] + 1.0) / 2.0;

        return {{x, 0, y}};
    }
};

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        throw std::runtime_error("Please provide a file name.");
    }

    MyVF vf;

    const char *fn = argv[1];
    writePpmImage(fn, 400, 100, vf);
}
