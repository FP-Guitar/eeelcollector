#include "dirwatcher/DirectoryFileListRetriever.h"

namespace eeelcollector::dirwatcher {
DirectoryFileListRetriever::DirectoryFileListRetriever(std::filesystem::path targetDirectory)
	: targetDirectory_{std::move(targetDirectory)} {}
std::vector<std::filesystem::path> DirectoryFileListRetriever::GetFiles() const {
  if (not exists(targetDirectory_)) {
	throw std::runtime_error("Target directory does not exist:" + targetDirectory_.string());
  }
  std::vector<std::filesystem::path> paths;
  for (const auto &path : std::filesystem::directory_iterator(targetDirectory_)) {
	if (is_regular_file(path)) { paths.push_back(path); }
  }
  std::sort(paths.begin(), paths.end());
  return paths;
}
}// namespace eeelcollector::dirwatcher
