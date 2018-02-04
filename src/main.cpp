#include <iostream>

#include "heimdall/geometry.h"
#include "heimdall/matrix.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, world!\n";

    heimdall::Vec3f v1(1.0, 0, 0);
    heimdall::Vec3f v2;
    heimdall::Vec3f v3;

    heimdall::CoordinateSystem(v1, &v2, &v3);

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
    return 0;
}

