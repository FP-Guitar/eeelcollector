#pragma once
#include <datacollector/TarFileStorage.hpp>
#include <datacollector/CollectionInfoObject.hpp>
#include <filesystem>

namespace eeelcollector::datacollector {

class TarFileStorage {
 public:
  explicit TarFileStorage(std::filesystem::path targetDirectory);
  void StoreObject(const CollectionInfoObject& object) const;
 private:
  std::filesystem::path targetDirectory_;

};
}




