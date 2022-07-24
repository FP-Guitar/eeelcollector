#include "appcontrol/Configuration.hpp"

#include <CLI/CLI.hpp>
#include <optional>
#include <string>
#include <filesystem>
#include <vector>

#include "internal_use_only/config.hpp"

namespace eeelcollector::appcontrol {
Configuration ParseArguments(int argc, const char **argv) {
  auto config = Configuration{};
  CLI::App app{fmt::format(
	  "{} version {}\n Tool will watch on specific directories and collect data if trigger file is found. See project readme for details.",
	  eeelcollector::cmake::project_name,
	  eeelcollector::cmake::project_version)};

  std::optional<std::string> watchDirectory;
  app.add_option("-w,--watch-directory", watchDirectory, "The directory to watch for files");

  bool show_version = false;
  app.add_flag("--version", show_version, "Show version information");

  std::optional<spdlog::level::level_enum> logLevel;
  app.add_option("-l,--log-level",
				 logLevel,
				 fmt::format("Log level from trace: {} to off: {}", spdlog::level::trace, spdlog::level::off));

  std::optional<std::filesystem::path> outputDirectory;
  app.add_option("-o,--output-directory", outputDirectory, "the directory to store the collected and tard files");

  std::vector<std::filesystem::path> files;
  app.add_option<std::vector<std::filesystem::path>>("-c,--collect-list",
													 files,
													 "The list of files to capture data from");

  // This is necessary as the original lib is intended to run in main. I'll personally like to have a small main.
  // And to have my command line parameters testable.
  try {
	app.parse(argc, argv);
  }
  catch (const CLI::ParseError &e) {
	config.returnCodeParsing = app.exit(e);
	config.errorParsing = true;
  }
  if (show_version) {
	config.showVersion = true;
  }
  if (logLevel) {
	config.logLevel = *logLevel;
  }
  if (outputDirectory) {
	config.outputDirectory = *outputDirectory;
  }

  config.watchDirectory = std::filesystem::path(".");
  if (watchDirectory) {
	config.watchDirectory = std::filesystem::path(*watchDirectory);
  }

  config.pathsToCollectDataFrom = files;
  return config;
}
}
