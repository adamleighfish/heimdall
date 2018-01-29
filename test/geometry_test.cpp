#include "gtest/gtest.h"
#include "heimdall/geometry.h"

TEST(Vec3f, VectorAddition) {
    Vec3f v1(1.0, 1.0, 1.0);
    Vec3f v2(2.0, 2.0, 2.0);
    Vec3f v3(3.0, 3.0, 3.0);

    Vec3f v4 = v1 + v2;
    v2 += v1;

    ASSERT_EQ(v4, v3);
    ASSERT_EQ(v2, v3);
    ASSERT_NE(v1, v3);
}

TEST(Vec3f, VectorSubtraction) {
    Vec3f v1(1.0, 1.0, 1.0);
    Vec3f v2(2.0, 2.0, 2.0);
    Vec3f v3(3.0, 3.0, 3.0);

    Vec3f v4 = v3 - v1;
    v3 -= v1;

    ASSERT_EQ(v4, v2);
    ASSERT_EQ(v3, v2);
    ASSERT_NE(v1, v2);
}

TEST(Vec3f, ScalarMuliplication) {
    Vec3f v1(1.0, 1.0, 1.0);
    Vec3f v2(2.0, 2.0, 2.0);
    Vec3f v3(3.0, 3.0, 3.0);
    double s = 2.0;

    Vec3f v4 = v1 * s;
    Vec3f v5 = s * v1;
    v1 *= s;

    ASSERT_EQ(v2, v4);
    ASSERT_EQ(v5, v2);
    ASSERT_EQ(v1, v2);
    ASSERT_NE(v3, v4);
}
