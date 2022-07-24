#pragma once
#include <vector>
#include <filesystem>
#include <datacollector/CollectionInfoObject.hpp>

namespace eeelcollector::datacollector {

class util {
 public:
  // Will return a vector containing all files at the given root. If the root is a file, will return the file
  // Will throw all exceptions possible when using std::filesystem. Will NOT follow symbolic links.
  // (avoid infinite recursion). Behaviour of state changes of root is not specified (as in std::filesystem::pathrecursive_directory_iterator)
  [[nodiscard]]static std::vector<std::filesystem::path> GetRecursiveDirectoryContents(const std::filesystem::path &root);
  // Will convert the json info object into a serialized json string
  [[nodiscard]]static std::string ConvertToJson(const CollectionInfoObject &obj);
  // Will have the form filename.unixseconds.uuid4
  [[nodiscard]]static std::string CreateUniqueIdentifierFromPath(const std::filesystem::path &path);
};
}




