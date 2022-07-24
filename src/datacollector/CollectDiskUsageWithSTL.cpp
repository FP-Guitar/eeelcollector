
#include "include/datacollector/CollectAvailableSpaceWithSTL.hpp"
#include <filesystem>
#include <string>
namespace eeelcollector::datacollector {
void CollectAvailableSpaceWithSTL::CollectData(CollectionInfoObject &collectionInfo) {
  auto info = std::filesystem::space(collectionInfo.collectionTarget);
  collectionInfo.additionalInformation["available"] = std::to_string(info.available);
  collectionInfo.additionalInformation["capacity"] = std::to_string(info.capacity);
  collectionInfo.additionalInformation["free"] = std::to_string(info.free);
}
}
