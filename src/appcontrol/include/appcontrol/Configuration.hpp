#pragma once
#include <vector>
#include <filesystem>
#include <spdlog/spdlog.h>

namespace eeelcollector::appcontrol {
struct Configuration {
  bool errorParsing = false;
  int returnCodeParsing = 0;
  std::vector<std::filesystem::path> pathsToCollectDataFrom;
  std::filesystem::path outputDirectory = ".";
  std::filesystem::path watchDirectory = ".";
  spdlog::level::level_enum logLevel = spdlog::level::info;
  bool showVersion = false;
};
Configuration ParseArguments(int argc, const char **argv);
}





