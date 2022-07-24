#pragma once
#include <datacollector/DataCollector.hpp>

namespace eeelcollector::datacollector  {
class CollectFilesAtTarget : public DataCollector{
 public:
  void CollectData(CollectionInfoObject &collectionInfo) override;
  ~CollectFilesAtTarget() override = default;

};
}




