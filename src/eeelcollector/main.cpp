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
#include <appcontrol/WatchTriggerDirectoryTask.h>
#include <appcontrol/Configuration.hpp>
#include <atomic>
#include <string>

std::atomic_bool run(true);
void signal_handler(int posixSignal) {
  (void)posixSignal;
  run = false;
}
const int STARTUPFAILURE = 1;
const int UNHANDLED_EXCEPTION = 2;

// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, const char **argv) {
  auto err = std::signal(SIGINT, signal_handler);

  // gcc9 uses some strange casting here
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
  if (err == SIG_ERR) {
	spdlog::error("Failure catching sigint");
	return STARTUPFAILURE;
  }

  try {
	auto config = eeelcollector::appcontrol::ParseArguments(argc,argv);
	if (config.errorParsing) {
	  return config.returnCodeParsing;
	}

	if (config.showVersion) {
	  fmt::print("{}\n", eeelcollector::cmake::project_version);
	  return EXIT_SUCCESS;
	}

	auto watchTask = eeelcollector::appcontrol::WatchTriggerDirectoryTask(config.watchDirectory);
	using namespace std::chrono_literals;
	while (run) {
	  watchTask.CheckDirectory();
	  std::this_thread::sleep_for(1s);

	  spdlog::info("Polling....");
	}
	spdlog::info("Shutting down...");
  } catch (const std::exception &e) {
	spdlog::error("Unhandled exception in main: {}", e.what());
	return UNHANDLED_EXCEPTION;
  }
  return 0;
}
