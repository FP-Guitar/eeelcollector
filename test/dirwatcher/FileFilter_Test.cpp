#include <dirwatcher/FilenameMatcher.h>
#include <gtest/gtest.h>
#include <list>
#include <string>

using namespace eeelcollector::dirwatcher;

TEST(FilenameMatcher, InvalidFileName)
{
  auto isMatch = FilenameMatcher();
  auto invalidString = std::string("FooBar");
  EXPECT_FALSE(isMatch(invalidString));
}
