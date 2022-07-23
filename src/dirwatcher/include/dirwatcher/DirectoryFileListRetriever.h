#pragma once
#include <filesystem>
#include <vector>

namespace eeelcollector::dirwatcher {
class DirectoryFileListRetriever {
 public:
  explicit DirectoryFileListRetriever(std::filesystem::path targetDirectory);
  // Return the files in the given directory in alphabetically order.
  // Will throw an instance of std::runtime_error if directory does not exist
  // The list will be sorted lexicographically.
  // directories are excluded.
  [[nodiscard]] std::vector<std::filesystem::path> GetFiles() const;
 private:
  std::filesystem::path targetDirectory_;
};
}
