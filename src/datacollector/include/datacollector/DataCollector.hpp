#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <datacollector/CollectionInfoObject.hpp>
namespace eeelcollector::datacollector {
class DataCollector {
 public:
  // Enrich the CollectionInfoObject with useful information
  virtual void CollectData(CollectionInfoObject& collectionInfo) = 0;
  virtual ~DataCollector() = default;
};
}



