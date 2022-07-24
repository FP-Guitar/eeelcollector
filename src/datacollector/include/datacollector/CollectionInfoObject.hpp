#pragma once
#include <filesystem>
#include <map>
#include <string>
namespace eeelcollector::datacollector {
struct CollectionInfoObject {
  std::filesystem::path collectionTarget;
  std::map<std::string,std::string> additionalInformation;
};
}


