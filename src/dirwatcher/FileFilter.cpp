#include "dirwatcher/FileFilter.h"
#include <algorithm>

#include <dirwatcher/FilenameMatcher.h>
namespace eeelcollector::dirwatcher {
std::vector<std::filesystem::path> eeelcollector::dirwatcher::FileFilter::Filter(
	const std::vector<std::filesystem::path> &pathList) {
  auto match = FilenameMatcher();
  auto filtered = std::vector<std::filesystem::path>();
  for (const auto &path : pathList) {
	if (match(path.filename().string())) {
	  filtered.push_back(path);
	}
  }
  return filtered;
}
}
