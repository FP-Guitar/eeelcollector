#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <vector>
namespace eeelcollector::datacollector {
struct CollectionInfoObject {
  std::filesystem::path collectionTarget;
  std::map<std::string, std::string> additionalInformation;
  std::vector<std::filesystem::path> collectedFiles;
};
}


