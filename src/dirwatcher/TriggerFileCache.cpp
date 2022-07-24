#include "dirwatcher/TriggerFileCache.h"
#include <algorithm>
#include <spdlog/spdlog.h>

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
  if (not diff.empty()) {
	spdlog::debug("Difference in Fileset");
	if (spdlog::get_level() <= spdlog::level::trace) {
	  for (const auto &file : diff) {
		spdlog::trace("NewFile: {}", file.string());
	  }
	}
  }

  return not diff.empty();
}

}// namespace eeelcollector::dirwatcher
