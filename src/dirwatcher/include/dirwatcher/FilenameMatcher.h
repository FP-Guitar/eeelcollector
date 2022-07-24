#pragma once
#include <regex>
#include <filesystem>
namespace eeelcollector::dirwatcher {

class FilenameMatcher {
 public:
  FilenameMatcher();
  bool operator()(const std::filesystem::path &filename) const;
 private:
  std::regex filenameMatch_;
};

}