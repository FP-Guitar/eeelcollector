#include "util.h"
std::filesystem::path getResourcesPath() {
#ifndef RESOURCES
  return {};
#else
  return std::filesystem::path{RESOURCES};
#endif
}

