#include <dirwatcher/FileFilter.h>
#include <gtest/gtest.h>
#include <list>

using namespace eeelcollector::dirwatcher;

TEST(FileFilterTest, FilterOutNonMatchingNames) {
  // Some notes if your wondering why I'll test not much here...
  // We know, we use internally the FilenameMatcher, so we don't test any edge cases,
  auto paths = std::vector<std::filesystem::path>{
	  "a", "b", "c", "core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4"
  };
  auto filteredList = FileFilter::Filter(paths);
  EXPECT_EQ(filteredList.size(), 1);
  EXPECT_EQ(filteredList[0], paths[3]);
}
TEST(FileFilterTest, FilterOutNonMatchingNamesHaveFullPaths) {
  // Some notes if your wondering why I'll test not much here...
  // We know, we use internally the FilenameMatcher, so we don't test any edge cases,
  auto paths = std::vector<std::filesystem::path>{
	  "a", "b", "c", "foo/core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4"
  };
  auto filteredList = FileFilter::Filter(paths);
  EXPECT_EQ(filteredList.size(), 1);
  EXPECT_EQ(filteredList[0], paths[3]);
}