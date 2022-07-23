#include <dirwatcher/TriggerFileCache.h>
#include <gtest/gtest.h>
using namespace eeelcollector::dirwatcher;
TEST(TriggerFileCache, FirstListOfFiles) {
  auto cache = TriggerFileCache();
  auto files = std::vector<std::filesystem::path>{"a", "b"};
  EXPECT_TRUE(cache.ContainsNewFiles(files));
}

TEST(TriggerFileCache, EmptyListOfFiles) {
  auto cache = TriggerFileCache();
  auto files = std::vector<std::filesystem::path>{};
  EXPECT_FALSE(cache.ContainsNewFiles(files));
}

TEST(TriggerFileCache, NoNewFiles) {
  auto cache = TriggerFileCache();
  auto files = std::vector<std::filesystem::path>{"a", "b"};
  auto files2 = std::vector<std::filesystem::path>{"a", "b"};

  EXPECT_TRUE(cache.ContainsNewFiles(files));
  EXPECT_FALSE(cache.ContainsNewFiles(files2));
}

TEST(TriggerFileCache, DeletionAndRecreationOfFile) {
  auto cache = TriggerFileCache();
  auto files = std::vector<std::filesystem::path>{"a", "b"};
  auto files2 = std::vector<std::filesystem::path>{"a"};
  auto files3 = std::vector<std::filesystem::path>{"a", "b"};
  EXPECT_TRUE(cache.ContainsNewFiles(files));
  EXPECT_FALSE(cache.ContainsNewFiles(files2));
  EXPECT_TRUE(cache.ContainsNewFiles(files3));
}

TEST(TriggerFileCache, DeletionOfAllFiles) {
  auto cache = TriggerFileCache();
  auto files = std::vector<std::filesystem::path>{"a", "b"};
  auto files2 = std::vector<std::filesystem::path>{};
  auto files3 = std::vector<std::filesystem::path>{"a", "b"};
  EXPECT_TRUE(cache.ContainsNewFiles(files));
  EXPECT_FALSE(cache.ContainsNewFiles(files2));
  EXPECT_TRUE(cache.ContainsNewFiles(files3));
}
