#pragma once
#include <string>
#include <regex>
namespace eeelcollector::dirwatcher {

class FilenameMatcher
{
public:
  FilenameMatcher();
  bool operator()(const std::string& filename) const;
private:
  std::regex filenameMatch_;
};

}