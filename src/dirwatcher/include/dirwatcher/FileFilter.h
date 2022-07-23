//
// Created by fabian-fp-bdim on 23.07.22.
//
#include <vector>
#include <filesystem>

#pragma once

namespace eeelcollector::dirwatcher {
class FileFilter {
 public:
  [[nodiscard]] static std::vector<std::filesystem::path> Filter(const std::vector<std::filesystem::path> &pathList);
};

}