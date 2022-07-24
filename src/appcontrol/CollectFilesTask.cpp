#include <spdlog/spdlog.h>
#include "include/appcontrol/CollectFilesTask.hpp"

namespace eeelcollector::appcontrol {
CollectFilesTask::CollectFilesTask(std::vector<std::unique_ptr<datacollector::DataCollector>> collectors,
								   std::filesystem::path target) : collectors_{std::move(collectors)},
																   targetPath_{std::move(target)} {
}

datacollector::CollectionInfoObject CollectFilesTask::Collect() const {
  auto info = datacollector::CollectionInfoObject{};
  info.collectionTarget = targetPath_;
  spdlog::info("Getting data from {}", targetPath_.string());
  for (const auto& collector : collectors_) {
	try {
	  collector->CollectData(info);
	}catch(std::runtime_error& e) {
	  spdlog::error("Failed to collet data {}", e.what());
	}
  }
  return info;
}
}



