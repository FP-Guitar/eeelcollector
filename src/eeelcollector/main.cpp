#include <optional>
#include <csignal>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include <thread>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `eeelcollector`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include "internal_use_only/config.hpp"
#include <vector>
#include <filewatchcontrol/WatchTriggerDirectoryTask.h>
#include <atomic>
#include <string>

std::atomic_bool run(true);
void signal_handler(int posixSignal) {
  (void)posixSignal;
  run = false;
}


// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, const char **argv) {
  auto err = std::signal(SIGINT,signal_handler);
  if  (err == SIG_ERR ) {
	spdlog::error("Failure catching sigint");
	return 1;
  }

  try {
	CLI::App app{fmt::format(
		"{} version {}", eeelcollector::cmake::project_name, eeelcollector::cmake::project_version)};

	std::optional<std::string> watchDirectory;
	app.add_option("-w,--watch-directory", watchDirectory, "The directory to watch for files");
	bool show_version = false;
	app.add_flag("--version", show_version, "Show version information");
	CLI11_PARSE(app, argc, argv);

	if (show_version) {
	  fmt::print("{}\n", eeelcollector::cmake::project_version);
	  return EXIT_SUCCESS;
	}
	auto pathToWatch = std::filesystem::path(".");
	if (watchDirectory) {
	  pathToWatch = std::filesystem::path(*watchDirectory);
	}

	auto watchTask = eeelcollector::filewatchcontrol::WatchTriggerDirectoryTask(pathToWatch);
	using namespace std::chrono_literals;
	while(run) {
	  watchTask.CheckDirectory();
	  std::this_thread::sleep_for(1s);

	  spdlog::info("Polling....");
	}
	if (watchDirectory) {
	  fmt::print("Message: '{}'\n", *watchDirectory);
	} else {
	  fmt::print("No Message Provided :(\n");
	}
  } catch (const std::exception &e) {
	spdlog::error("Unhandled exception in main: {}", e.what());
  }
}
