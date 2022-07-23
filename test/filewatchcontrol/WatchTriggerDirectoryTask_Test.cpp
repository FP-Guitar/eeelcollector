
#include <filewatchcontrol/WatchTriggerDirectoryTask.h>
#include <gtest/gtest.h>
std::filesystem::path getResourcesPath() {
#ifndef RESOURCES
  return {};
#else
  return std::filesystem::path{RESOURCES};
#endif
}
using namespace eeelcollector::filewatchcontrol;
TEST(FilewatchControl, WatchTriggerDirectoryTaskEmptyDirectory) {
  auto task = WatchTriggerDirectoryTask(std::filesystem::path{});
  EXPECT_FALSE(task.CheckDirectory());
}

TEST(FilewatchControl, WatchTriggerDirectoryTaskCorrectDirectory) {
  auto task = WatchTriggerDirectoryTask(getResourcesPath());
  EXPECT_FALSE(task.CheckDirectory());
}

TEST(FilewatchControl, WatchTriggerDirectoryTaskCorrectDirectoryWithCorrectFile) {
  auto task = WatchTriggerDirectoryTask(getResourcesPath()/="filelistscenario/c");
  EXPECT_TRUE(task.CheckDirectory());
}
