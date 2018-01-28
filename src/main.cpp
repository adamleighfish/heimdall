#include <iostream>

#include "geometry.h"

int main(int argc, char* argv[]) {
    Vec3f myVec(1.0, 2.0, 3.0);
    std::cout << myVec.x << " " << myVec.y << " " << myVec.z << std::endl;
    return 0;
}
