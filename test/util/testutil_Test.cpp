#include <gtest/gtest.h>
#include <testutil.h>
TEST(UtilTest, GetResourcesDirectory) { EXPECT_TRUE(is_directory(getResourcesPath())); }

