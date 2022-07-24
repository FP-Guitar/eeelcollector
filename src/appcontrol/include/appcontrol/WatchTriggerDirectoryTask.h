#pragma once
#include <filesystem>
#include <dirwatcher/DirectoryFileListRetriever.h>
#include <dirwatcher/TriggerFileCache.h>

namespace eeelcollector::appcontrol {
using TriggerFileDetected = bool;
class WatchTriggerDirectoryTask {
 public:
  explicit WatchTriggerDirectoryTask(std::filesystem::path pathToWatch);
  TriggerFileDetected CheckDirectory();
 private:
  std::filesystem::path pathToWatch_;
  dirwatcher::TriggerFileCache triggerFileCache_;
};
}




