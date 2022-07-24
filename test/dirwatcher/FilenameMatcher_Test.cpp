#include <dirwatcher/FilenameMatcher.h>
#include <gtest/gtest.h>
#include <list>

using namespace eeelcollector::dirwatcher;

TEST(FilenameMatcher, InvalidFileName) {
  auto isMatch = FilenameMatcher();
  auto invalidPath = std::filesystem::path("FooBar");
  EXPECT_FALSE(isMatch(invalidPath));
}

TEST(FilenameMatcher, InvValidFileNameTwoServiceNames) {
  auto isMatch = FilenameMatcher();
  auto validPath =
	  std::filesystem::path("core.ServiceName.Foobar.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4");
  EXPECT_FALSE(isMatch(validPath));
}
TEST(FilenameMatcher, InvValidFileNameCoreMissing) {
  auto isMatch = FilenameMatcher();
  auto validPath = std::filesystem::path("ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4");
  EXPECT_FALSE(isMatch(validPath));
}

TEST(FilenameMatcher, InvValidFileNamelz4Missing) {
  auto isMatch = FilenameMatcher();
  auto
	  validPath = std::filesystem::path("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000");
  EXPECT_FALSE(isMatch(validPath));
}

TEST(FilenameMatcher, InvValidFileNamelz4iwthoutdotMissing) {
  auto isMatch = FilenameMatcher();
  auto validPath =
	  std::filesystem::path("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000lz4");
  EXPECT_FALSE(isMatch(validPath));
}

TEST(FilenameMatcher, ValidFileName) {
  auto isMatch = FilenameMatcher();
  auto validPath =
	  std::filesystem::path("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4");
  EXPECT_TRUE(isMatch(validPath));
}

TEST(FilenameMatcher, ValidFileNameAllPossibleHexDigits) {
  auto isMatch = FilenameMatcher();
  auto validPath = std::filesystem::path("core.ServiceName.abcdef.ABCDEF.01234567890.lz4");
  EXPECT_TRUE(isMatch(validPath));
}

TEST(FilenameMatcher, ValidFileNameOnlyOneHexDigitGroup) {
  auto isMatch = FilenameMatcher();
  auto validPath = std::filesystem::path("core.ServiceName.57dd721409bc4ab4b38a3c33a36a608a.lz4");
  EXPECT_TRUE(isMatch(validPath));
}

TEST(FilenameMatcher, ValidFileNameDifferentServiceName) {
  auto isMatch = FilenameMatcher();
  auto validPath = std::filesystem::path("core.FoOBar.57dd721409bc4ab4b38a3c33a36a608a.lz4");
  EXPECT_TRUE(isMatch(validPath));
}

TEST(FilenameMatcher, ValidFileNameNoServiceName) {
  auto isMatch = FilenameMatcher();
  auto validPath = std::filesystem::path("core.57dd721409bc4ab4b38a3c33a36a608a.lz4");
  EXPECT_TRUE(isMatch(validPath));
}