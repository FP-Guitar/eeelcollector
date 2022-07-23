#pragma once
#include <vector>
#include <filesystem>
#include <set>

namespace eeelcollector::dirwatcher {
class TriggerFileCache {
 public:
  // Consumes a list of files. If the list contains any new file  in comparison
  // to the last call --> true, else --> false
  bool ContainsNewFiles(std::vector<std::filesystem::path> &fileList);

 private:
  std::set<std::filesystem::path> lastSeenFiles_;
};
}
