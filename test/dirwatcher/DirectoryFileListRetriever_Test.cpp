#include <dirwatcher/DirectoryFileListRetriever.h>
#include <gtest/gtest.h>

std::filesystem::path getResourcesPath() {
#ifndef RESOURCES
  return {};
#else
  return std::filesystem::path{RESOURCES};
#endif
}
using namespace eeelcollector::dirwatcher;
TEST(DirectoryFileListRetriever, GetResourcesDirectory) { EXPECT_TRUE(is_directory(getResourcesPath())); }

TEST(DirectoryFileListRetriever, CreateFileListRetriever) {
  auto emptyPath = std::filesystem::path();
  auto retriever = DirectoryFileListRetriever(emptyPath);
  (void)retriever;
}

TEST(DirectoryFileListRetriever, GetFileList) {
  auto pathToA = getResourcesPath() /= std::filesystem::path("filelistscenario") /= std::filesystem::path("a");
  auto fileLister = DirectoryFileListRetriever(pathToA);

  auto files = fileLister.GetFiles();
  EXPECT_EQ(files.size(), 2);
  EXPECT_EQ(files[0].filename(), std::filesystem::path("a_foo1.txt"));
  EXPECT_EQ(files[1].filename(), std::filesystem::path("a_foo2.txt"));
}

TEST(DirectoryFileListRetriever, GetFileListDirectoryDoesNotExist) {
  auto invalidPath = std::filesystem::path("IDoNotExist");
  auto fileLister = DirectoryFileListRetriever(invalidPath);

  // workaround for [[no discard]]
  EXPECT_THROW(
	  {
		auto foo = fileLister.GetFiles();
		(void)foo;
	  },
	  std::runtime_error);
}

TEST(DirectoryFileListRetriever, GetFileListDirectoryIsAFile) {
  auto pathToFile = getResourcesPath() /= std::filesystem::path("filelistscenario") /= std::filesystem::path("a") /=
	  std::filesystem::path("a_foo1.txt");
  auto fileLister = DirectoryFileListRetriever(pathToFile);

  // workaround for [[no discard]]
  EXPECT_THROW(
	  {
		auto foo = fileLister.GetFiles();
		(void)foo;
	  },
	  std::runtime_error);
  // thrown by directory_iterator used internally
}
