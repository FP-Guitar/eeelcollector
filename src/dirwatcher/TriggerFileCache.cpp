#include "dirwatcher/TriggerFileCache.h"
#include <algorithm>

namespace eeelcollector::dirwatcher {
bool TriggerFileCache::ContainsNewFiles(std::vector<std::filesystem::path> &fileList) {
  std::set<std::filesystem::path> inputSet;
  std::set<std::filesystem::path> diff;
  std::copy(fileList.begin(), fileList.end(), std::inserter(inputSet, inputSet.end()));
  std::set_difference(
	  inputSet.begin(),
	  inputSet.end(),
	  lastSeenFiles_.begin(),
	  lastSeenFiles_.end(),
	  std::inserter(diff, diff.end()));

  lastSeenFiles_ = inputSet;
  return not diff.empty();
}

}// namespace eeelcollector::dirwatcher
