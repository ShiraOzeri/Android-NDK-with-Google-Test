#include <gtest/gtest.h>
#include "foo.h"
TEST(FooTest,ZeroZero) {
EXPECT_EQ(0, foo(0, 0));
}
TEST(FooTest,OneOne) {
EXPECT_EQ(2, foo(1, 1));
}