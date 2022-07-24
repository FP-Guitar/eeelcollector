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
	  "{} version {}", eeelcollector::cmake::project_name, eeelcollector::cmake::project_version)};

  std::optional<std::string> watchDirectory;
  app.add_option("-w,--watch-directory", watchDirectory, "The directory to watch for files");

  bool show_version = false;
  app.add_flag("--version", show_version, "Show version information");

  std::vector<std::filesystem::path> files;
  app.add_option<std::vector<std::filesystem::path>>("-c,--collect-list",files, "The list of files to capture data from");
  config.pathsToCollectDataFrom = files;


  try {
	app.parse(argc, argv);
  }
  catch (const CLI::ParseError &e)
  {
	config.returnCodeParsing = app.exit(e);
	config.errorParsing = true;
  }

  if (show_version) {
	config.showVersion = true;
  }
  config.watchDirectory = std::filesystem::path(".");
  if (watchDirectory) {
	config.watchDirectory = std::filesystem::path(*watchDirectory);
  }
  for (const auto& file : files) {
	std::cout << file.filename();
  }

  return config;
}
}
