#pragma once
#include <vector>
#include <filesystem>

namespace eeelcollector::datacollector {

class util {
  // Will return a vector containing all files at the given root. If the root is a file, will return the file
  // Will throw all exceptions possible when using std::filesystem. Will NOT follow symbolic links.
  // (avoid infinite) recursion). Behaviour of state changes of root is not specified (as in std::filesystem::pathrecursive_directory_iterator)
  static std::vector<std::filesystem::path> GetRecursiveDirectoryContents(const std::filesystem::path& root);

};
}




