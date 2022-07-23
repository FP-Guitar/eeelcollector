#include <dirwatcher/FilenameMatcher.h>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace eeelcollector::dirwatcher;


TEST(FilenameMatcher, CreateFilenameMatcher)
{
  auto matcher = FilenameMatcher();
  (void)matcher;
}

TEST(FilenameMatcher, InvalidFileName)
{
  auto isMatch = FilenameMatcher();
  auto invalidString = std::string("FooBar");
  EXPECT_FALSE(isMatch(invalidString));
}

TEST(FilenameMatcher, InvValidFileNameTwoServiceNames)
{
  auto isMatch = FilenameMatcher();
  auto validString =
    std::string("core.ServiceName.Foobar.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4");
  EXPECT_FALSE(isMatch(validString));
}
TEST(FilenameMatcher, InvValidFileNameCoreMissing)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4");
  EXPECT_FALSE(isMatch(validString));
}

TEST(FilenameMatcher, InvValidFileNamelz4Missing)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000");
  EXPECT_FALSE(isMatch(validString));
}

TEST(FilenameMatcher, InvValidFileNamelz4iwthoutdotMissing)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000lz4");
  EXPECT_FALSE(isMatch(validString));
}

TEST(FilenameMatcher, ValidFileName)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4");
  EXPECT_TRUE(isMatch(validString));
}

TEST(FilenameMatcher, ValidFileNameAllPossibleHexDigits)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.ServiceName.abcdef.ABCDEF.01234567890.lz4");
  EXPECT_TRUE(isMatch(validString));
}

TEST(FilenameMatcher, ValidFileNameOnlyOneHexDigitGroup)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.ServiceName.57dd721409bc4ab4b38a3c33a36a608a.lz4");
  EXPECT_TRUE(isMatch(validString));
}

TEST(FilenameMatcher, ValidFileNameDifferentServiceName)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.FoOBar.57dd721409bc4ab4b38a3c33a36a608a.lz4");
  EXPECT_TRUE(isMatch(validString));
}


TEST(FilenameMatcher, ValidFileNameNoServiceName)
{
  auto isMatch = FilenameMatcher();
  auto validString = std::string("core.57dd721409bc4ab4b38a3c33a36a608a.lz4");
  EXPECT_TRUE(isMatch(validString));
}