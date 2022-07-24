#include "include/datacollector/util.h"
#include "include/datacollector/DataCollector.hpp"
#include <nlohmann/json.hpp>
#include <sstream>
#include <chrono>
#include <uuid.h>

std::vector<std::filesystem::path> eeelcollector::datacollector::util::GetRecursiveDirectoryContents(const std::filesystem::path &root) {
  std::vector<std::filesystem::path> files{};
  auto recursiveDirectoryIterator = std::filesystem::recursive_directory_iterator(root);
  std::copy(begin(recursiveDirectoryIterator), end(recursiveDirectoryIterator), std::inserter(files, files.begin()));
  std::sort(files.begin(), files.end());
  return files;
}

std::string eeelcollector::datacollector::util::ConvertToJson(const eeelcollector::datacollector::CollectionInfoObject &obj) {
  const char *collectionTargetFieldName = "collectionTarget";
  const char *additionalTargetFieldName = "additionalInformation";
  const char *fileListFileListName = "fileList";
  const int prettyPrintIndent = 4;

  nlohmann::json json;
  json[collectionTargetFieldName] = obj.collectionTarget;
  if (obj.additionalInformation.empty()) {
	// Make sure json structure is always the same...Would prefer to use json schema or similar stuff for this
	json[additionalTargetFieldName]["None"] = "Provided";
  } else {
	for (const auto &keyValuePair : obj.additionalInformation) {
	  json[additionalTargetFieldName][keyValuePair.first] = keyValuePair.second;
	}
  }
  if (obj.collectedFiles.empty()) {
	json[fileListFileListName] = nlohmann::json::array();
  } else {
	auto fileList = nlohmann::json::array();
	std::transform(obj.collectedFiles.begin(),
				   obj.collectedFiles.end(),
				   std::inserter(fileList, fileList.begin()),
				   [](const std::filesystem::path &pat) { return pat.string(); });

	json[fileListFileListName] = fileList;
  }
  return json.dump(prettyPrintIndent);
}

std::string eeelcollector::datacollector::util::CreateUniqueIdentifierFromPath(const std::filesystem::path &path) {
  // could be easily optimzied to object with one time initilaizioatn
  std::random_device randomdDevice;
  std::mt19937 generator(randomdDevice());
  auto gen = uuids::basic_uuid_random_generator{&generator};
  std::stringstream identifier;
  identifier << path.filename().string();
  identifier << '.';
  auto now = std::chrono::system_clock::now();
  identifier << '.';

  identifier << std::to_string(now.time_since_epoch().count());
  identifier << gen();
  return identifier.str();
}
