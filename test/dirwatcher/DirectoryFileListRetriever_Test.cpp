#include <gtest/gtest.h>
#include <dirwatcher/DirectoryFileListRetriever.h>

TEST(DirectoryFileListRetriever, CreateFileListRetriever)
{
  auto retriever = DirectoryFileListRetriever();
  (void)retriever;
}

