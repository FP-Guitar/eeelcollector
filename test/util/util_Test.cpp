#include <gtest/gtest.h>
#include <util.h>
TEST(UtilTest, GetResourcesDirectory) { EXPECT_TRUE(is_directory(getResourcesPath())); }

