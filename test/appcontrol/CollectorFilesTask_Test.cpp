#include <gtest/gtest.h>
#include "testutil.h"
#include "appcontrol/CollectFilesTask.hpp"

using namespace eeelcollector::appcontrol;
using namespace eeelcollector::datacollector;
class MockDataCollector : public eeelcollector::datacollector::DataCollector {
 public:
  explicit MockDataCollector(std::string name) : name_{std::move(name)} {}
  void CollectData(CollectionInfoObject &collectionInfo) override {
	collectionInfo.additionalInformation[name_] = "called";
  }
  ~MockDataCollector() override = default;
  std::string name_;
};

TEST(CollectorTaskTest, ExampleScenario) {
  auto scenarioPath = getResourcesPath() /= "filelistscenario";
  std::vector<std::unique_ptr<DataCollector>> collectors{};
  collectors.push_back(std::make_unique<MockDataCollector>("b")),
	  collectors.push_back(std::make_unique<MockDataCollector>("a"));
  CollectFilesTask task{std::move(collectors), scenarioPath};
  auto infoObject = task.Collect();
  EXPECT_TRUE(infoObject.additionalInformation.contains("a"));
  EXPECT_TRUE(infoObject.additionalInformation.contains("b"));
}

