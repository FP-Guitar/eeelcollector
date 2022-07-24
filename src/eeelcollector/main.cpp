#include <optional>
#include <csignal>

#include <spdlog/spdlog.h>
#include <thread>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `eeelcollector`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include "internal_use_only/config.hpp"
#include <vector>
#include <appcontrol/WatchTriggerDirectoryTask.h>
#include <appcontrol/Configuration.hpp>
#include <appcontrol/CollectFilesTask.hpp>

#include <datacollector/CollectFilesAtTarget.hpp>
#include <datacollector/CollectAvailableSpaceWithSTL.hpp>
#include <datacollector/util.h>
#include <atomic>
#include <future>

using namespace eeelcollector;
void CollectData(appcontrol::Configuration const &config);
void DoFileWatching(appcontrol::Configuration const &config);
// This is probably not the best way, but I never used sigaction. But this is still better
// Than unhandled sigint.
std::atomic_bool run(true);
void signal_handler(int posixSignal) {
  static_cast<void>(posixSignal);
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
	auto config = eeelcollector::appcontrol::ParseArguments(argc, argv);
	if (config.errorParsing) {
	  return config.returnCodeParsing;
	}

	if (config.showVersion) {
	  fmt::print("{}\n", eeelcollector::cmake::project_version);
	  return EXIT_SUCCESS;
	}
	spdlog::info(fmt::format("Setting loglevel to {}", config.logLevel));
	spdlog::set_level(config.logLevel);

	DoFileWatching(config);

	spdlog::info("Shutting down...");
  } catch (const std::exception &e) {
	spdlog::error("Unhandled exception in main: {}", e.what());
	return UNHANDLED_EXCEPTION;
  }
  return 0;
}

void DoFileWatching(appcontrol::Configuration const &config) {
  auto watchTask = eeelcollector::appcontrol::WatchTriggerDirectoryTask(config.watchDirectory);
  using namespace std::chrono_literals;
  while (run) {
	spdlog::info("Polling....");
	if (watchTask.CheckDirectory()) {
	  CollectData(config);
	}
	std::this_thread::sleep_for(1s);
  }
}

void CollectData(appcontrol::Configuration const &config) {
  std::vector<std::future<datacollector::CollectionInfoObject>> collectedData{};
  for (const auto &path : config.pathsToCollectDataFrom) {
	spdlog::info("Starting collection on: {}", path.filename().c_str());
	std::vector<std::unique_ptr<datacollector::DataCollector>> collectors{};
	collectors.push_back(std::make_unique<datacollector::CollectFilesAtTarget>());
	collectors.push_back(std::make_unique<datacollector::CollectAvailableSpaceWithSTL>());
	collectedData.push_back(std::async(&appcontrol::CollectFilesTask::Collect,
									   appcontrol::CollectFilesTask(std::move(collectors), path)));
  }
  for (std::future<datacollector::CollectionInfoObject> &result : collectedData) {
	try {
	  auto res = result.get();
	  spdlog::info("Getting result from: {}", res.collectionTarget.c_str());
	  spdlog::info(datacollector::util::ConvertToJson(res));
	} catch (std::runtime_error &e) {
	  spdlog::error("Failure collection... {}", e.what());
	}
  }
}
