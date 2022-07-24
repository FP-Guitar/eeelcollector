#include "datacollector/CollectFilesAtTarget.hpp"
#include "datacollector/util.h"
void eeelcollector::datacollector::CollectFilesAtTarget::CollectData(eeelcollector::datacollector::CollectionInfoObject &collectionInfo) {
  try {
	collectionInfo.collectedFiles = util::GetRecursiveDirectoryContents(collectionInfo.collectionTarget);
  } catch (std::runtime_error &e) {
	std::throw_with_nested(std::runtime_error(
		std::string("Failed to get file list from:") + collectionInfo.collectionTarget.string()));
  }
}
