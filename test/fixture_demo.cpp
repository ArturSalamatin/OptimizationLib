#include <gtest/gtest.h>

#include <iostream>

#include <optlib/Points/SetOfPoints/PointVals/Point/Point.h>
#include <optlib/Points/SetOfPoints/PointVals/Point/PointOperators.h>

using namespace OptLib;


struct PointFixture 
    : public testing::Test
{
    Point<3> rp1;
    Point<3> rp2;

    void SetUp() override
    {
        std::cout << "PointFixture::SetUp" << std::endl;

        rp1 = Point<3>{1.0, 2.0, 3.0};
        rp2 = Point<3>{1.0, 2.0, 3.0};
    }

    void TearDown() override
    {
        std::cout << "PointFixture::TearDown" << std::endl;
    }

};

TEST_F(PointFixture, funcs) {
    ASSERT_NO_THROW(double r1{dot_product(rp1, rp2)});
    ASSERT_NO_THROW(double r2{norm(rp1)});
    ASSERT_NO_THROW(double r3{dist(rp1, rp2)});

    double r1{dot_product(rp1, rp2)};
    double r2{norm(rp1)};
    double r3{dist(rp1, rp2)};

    ASSERT_GE(r2, 3.0);
    ASSERT_LE(r2, 4.0);
}

TEST_F(PointFixture, operators) {

    Point<3> rp6{2.0, 1.0, 3.0};
     // testing Point operators
    ASSERT_NO_THROW(std::cout << rp6 << std::endl);
    rp6 += 3.0;
    rp6 -= 3.0;
    rp6 *= 2.5;
    rp6 /= 2.5;

    auto rp7{rp6 + 1.0};
    auto rp8{rp6 - 1.0};
    auto rp9 = rp6 * 2.0;
    auto rp91 = 2.0 * rp6;
    auto rp10 = rp6 / 2.0;
    auto rp11 = abs(rp6);
    auto rp12 = sqrt(rp6);
    auto rp13 = rp6 / 2.0;
    auto rp14 = rp6 / 2.0;
    auto rp15{1.0 + rp6};
    auto rp16{1.0 - rp6};

    ASSERT_EQ(0, 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}