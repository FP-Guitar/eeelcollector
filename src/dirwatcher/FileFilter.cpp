#include "dirwatcher/FileFilter.h"
#include <algorithm>

#include <dirwatcher/FilenameMatcher.h>
namespace eeelcollector::dirwatcher {
std::vector<std::filesystem::path> eeelcollector::dirwatcher::FileFilter::Filter(
	const std::vector<std::filesystem::path> &pathList) {
  auto match = FilenameMatcher();
  auto filtered = std::vector<std::filesystem::path>();
  std::copy_if(pathList.begin(),pathList.end(), std::inserter(filtered, filtered.begin()), match);
  return filtered;
}
}
