#include "gtest/gtest.h"
#include "heimdall/geometry.h"

TEST(Vec3f, Addition)
{
    Vec3f v1(1.0, 1.0, 1.0);
    Vec3f v2(2.0, 2.0, 2.0);
    Vec3f v3(3.0, 3.0, 3.0);

    Vec3f v4 = v1 + v2;
    v2 += v1;

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(v4[i], v3[i]);
        ASSERT_EQ(v2[i], v3[i]);
    }
}
