
#include "include/appcontrol/WatchTriggerDirectoryTask.h"
#include <spdlog/spdlog.h>
#include <dirwatcher/FileFilter.h>
namespace eeelcollector::appcontrol {

WatchTriggerDirectoryTask::WatchTriggerDirectoryTask(std::filesystem::path pathToWatch) :
	pathToWatch_(std::move(pathToWatch)) {
  spdlog::info("WatchTriggerDirectoryTask started. Watching on path: {}", pathToWatch_.string());
}

void dumpIfDebugLogLevel(const std::vector<std::filesystem::path> &list);
TriggerFileDetected WatchTriggerDirectoryTask::CheckDirectory() {
  try {
	auto retriever = dirwatcher::DirectoryFileListRetriever(pathToWatch_);
	auto list = dirwatcher::FileFilter::Filter(retriever.GetFiles());
	dumpIfDebugLogLevel(list);
	auto newFile = triggerFileCache_.ContainsNewFiles(list);
	if (newFile) {
	  spdlog::info("Found new file: {}", newFile);
	}
	spdlog::debug("Found new file: {}", newFile);
	return newFile;
  } catch (std::runtime_error &e) {
	spdlog::error("Could not process file list {}", e.what());
	return false;
  }
}
void dumpIfDebugLogLevel(const std::vector<std::filesystem::path> &list) {
  spdlog::debug("Retrieved a file list of size {}", list.size());
  if (spdlog::get_level() <= spdlog::level::debug) {
	for (const auto &path : list) {
	  spdlog::info("file {}", path.string());
	}
  }
}
}
