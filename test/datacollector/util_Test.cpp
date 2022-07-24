#include <gtest/gtest.h>
#include <testutil.h>

#include <datacollector/util.h>
#include <nlohmann/json.hpp>

using namespace eeelcollector::datacollector;
TEST(UtilTest, RetrieveFiles) {
  auto scenarioPath = getResourcesPath() /= "filelistscenario";
  auto fileList = util::GetRecursiveDirectoryContents(scenarioPath);
  EXPECT_EQ( fileList.size(), 8);
  EXPECT_EQ(fileList[0].filename(), std::filesystem::path("a"));

  EXPECT_EQ(fileList[7].filename(), std::filesystem::path("core.ServiceName.3057.57dd721409bc4ab4b38a3c33a36a608a.3717.1647975805000000.lz4"));
}

TEST(UtilTest, ConvertToJsonCheckStructure) {
  CollectionInfoObject information;
  information.collectionTarget = std::filesystem::path("FooBar");
  auto jsonString = util::ConvertToJson(information);
  auto json = nlohmann::json::parse(jsonString);
  EXPECT_TRUE(json.contains("collectionTarget"));
  EXPECT_TRUE(json.contains("additionalInformation"));
  EXPECT_TRUE(json.contains("fileList"));
}

TEST(UtilTest, ConvertToJsonCheckValues) {
  CollectionInfoObject information;
  information.collectionTarget = std::filesystem::path("FooBar");
  information.additionalInformation["A"] ="A";
  information.additionalInformation["CT5555"] ="Fives";
  information.collectedFiles = std::vector<std::filesystem::path>{"a","b"};

  auto jsonString = util::ConvertToJson(information);
  auto json = nlohmann::json::parse(jsonString);
  EXPECT_EQ(json["collectionTarget"], "FooBar");
  EXPECT_EQ(json["additionalInformation"]["A"], "A");
  EXPECT_EQ(json["additionalInformation"]["CT5555"], "Fives");
  EXPECT_EQ(json["fileList"][0], "a");
}


TEST(UtilTest, CreateUniqueIdentifierFromPath) {
  auto path = std::filesystem::path("Foo");
  auto identifier1 = util::CreateUniqueIdentifierFromPath(path);

  auto identifier2 = util::CreateUniqueIdentifierFromPath(path);
  EXPECT_NE(identifier1,identifier2);
}