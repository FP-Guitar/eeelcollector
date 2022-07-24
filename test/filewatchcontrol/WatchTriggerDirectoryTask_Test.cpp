
#include <filewatchcontrol/WatchTriggerDirectoryTask.h>
#include <gtest/gtest.h>
#include <testutil.h>

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
