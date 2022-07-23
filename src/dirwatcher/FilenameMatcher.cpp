#include "include/dirwatcher//FilenameMatcher.h"

namespace eeelcollector::dirwatcher {


FilenameMatcher::FilenameMatcher():filenameMatch_{R"((?:core(?:\.\w*)\.)(?:[abcdef01234567890]+\.)*lz4)", std::regex::icase} {

}

bool FilenameMatcher::operator()(const std::string& filename) const{
  return std::regex_match(filename,filenameMatch_);
};


}
