#pragma once
#include <datacollector/DataCollector.hpp>
#include <datacollector/CollectionInfoObject.hpp>
#include <memory>

namespace eeelcollector::appcontrol {

class CollectFilesTask {
 public:
  CollectFilesTask(std::vector<std::unique_ptr<datacollector::DataCollector>> collectors, std::filesystem::path target);
  datacollector::CollectionInfoObject Collect() const;
 private:
  std::vector<std::unique_ptr<datacollector::DataCollector>> collectors_;
  std::filesystem::path targetPath_;

};

}




