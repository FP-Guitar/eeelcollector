#include <gtest/gtest.h>
#include <testutil.h>
#include <datacollector/CollectFilesAtTarget.hpp>

using namespace eeelcollector::datacollector;
TEST(CollectFilesTest, ExampleScenario) {
  auto scenarioPath = getResourcesPath() /= "filelistscenario";
  CollectionInfoObject infoObject;
  infoObject.collectionTarget = scenarioPath;

  CollectFilesAtTarget collector;

  collector.CollectData(infoObject);
  EXPECT_EQ(infoObject.collectedFiles.size(),8);
  EXPECT_EQ(infoObject.collectedFiles[0].filename(),std::filesystem::path("a") );
}
