#pragma once
#include <datacollector/DataCollector.hpp>
#include <datacollector/CollectionInfoObject.hpp>

namespace eeelcollector::datacollector {
class CollectAvailableSpaceWithSTL : public DataCollector {
 public:
  void CollectData(CollectionInfoObject &collectionInfo) override;
  ~CollectAvailableSpaceWithSTL() override = default;
};
}





