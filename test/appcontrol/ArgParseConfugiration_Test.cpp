#include <gtest/gtest.h>
#include <testutil.h>
#include <appcontrol/Configuration.hpp>
#include <vector>
using namespace eeelcollector::appcontrol;

TEST(ConfigurationTest, OneCompleteSetOfFlags) {
  // c++ argc/argv is what it is...
  // NOLINTNEXTLINE
  int argc = 10;
  // c++ argc/argv is what it is...
  // NOLINTNEXTLINE
  const char *argv[] = {
	  "eeelcollector",
	  "-w", "foo",
	  "--log-level", "1",
	  "-o", "c",
	  "-c", "a", "b",
  };
  // c++ argc/argv is what it is...
  // NOLINTNEXTLINE
  auto configuration = ParseArguments(argc, argv);
  auto expectedPaths = std::vector<std::filesystem::path>{"a", "b"};

  EXPECT_EQ(configuration.pathsToCollectDataFrom, expectedPaths);
  EXPECT_EQ(configuration.watchDirectory, std::filesystem::path("foo"));
  EXPECT_EQ(configuration.outputDirectory, std::filesystem::path("c"));
  EXPECT_EQ(configuration.logLevel, spdlog::level::debug);
}


