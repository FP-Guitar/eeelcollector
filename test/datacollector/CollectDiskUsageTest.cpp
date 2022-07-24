

#include <gtest/gtest.h>
#include <testutil.h>
#include <datacollector/CollectAvailableSpaceWithSTL.hpp>

using namespace eeelcollector::datacollector;
TEST(CollectDiskUsageTest, UseStlWithDirectory) {
  auto scenarioPath = getResourcesPath() /= "filelistscenario";
  CollectionInfoObject infoObject;
  infoObject.collectionTarget = scenarioPath;

  CollectAvailableSpaceWithSTL collector;
  collector.CollectData(infoObject);
  EXPECT_EQ(infoObject.additionalInformation.size(), 3);
  EXPECT_TRUE(infoObject.additionalInformation.contains("available"));
  EXPECT_TRUE(infoObject.additionalInformation.contains("free"));
  EXPECT_TRUE(infoObject.additionalInformation.contains("capacity"));

  for (const auto &kevalues : infoObject.additionalInformation) {
	std::cout << kevalues.first << ':' << kevalues.second << std::endl;
  }
}

TEST(CollectDiskUsageTest, UseStlWithDirectoryFile) {
  auto scenarioPath = getResourcesPath() /= "filelistscenario/a/a_foo1.txt";
  CollectionInfoObject infoObject;
  infoObject.collectionTarget = scenarioPath;

  CollectAvailableSpaceWithSTL collector;
  collector.CollectData(infoObject);
  EXPECT_EQ(infoObject.additionalInformation.size(), 3);
  EXPECT_TRUE(infoObject.additionalInformation.contains("available"));
  EXPECT_TRUE(infoObject.additionalInformation.contains("free"));
  EXPECT_TRUE(infoObject.additionalInformation.contains("capacity"));

  for (const auto &kevalues : infoObject.additionalInformation) {
	std::cout << kevalues.first << ':' << kevalues.second << std::endl;
  }
}
