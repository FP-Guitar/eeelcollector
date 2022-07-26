#include "include/datacollector/util.h"
#include <nlohmann/json.hpp>
#include <sstream>
#include <chrono>
#include <uuid.h>

std::vector<std::filesystem::path> eeelcollector::datacollector::util::GetRecursiveDirectoryContents(const std::filesystem::path &root) {
  if (is_regular_file(root)) {
	return {root};
  }

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

  // Make sure json structure is always the same...Would prefer to use json schema or similar stuff for this
  nlohmann::json json;
  json[collectionTargetFieldName] = obj.collectionTarget;
  if (obj.additionalInformation.empty()) {
	json[additionalTargetFieldName]["None"] = "Provided";
  } else {
	for (const auto &keyValuePair : obj.additionalInformation) {
	  json[additionalTargetFieldName][keyValuePair.first] = keyValuePair.second;
	}
  }

  json[fileListFileListName] = nlohmann::json::array();
  if (not obj.collectedFiles.empty()) {
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
  auto directory_as_string = path.string();
  if (directory_as_string == "/") {
	// we do not want to have / in a filename
	identifier << "rootfs";
  } else if (directory_as_string.ends_with("/")) {
	identifier << path.parent_path().filename().string();
  } else {
	identifier << path.filename().string();
  }
  identifier << '-';

  auto now = std::chrono::system_clock::now();
  identifier << std::to_string(now.time_since_epoch().count());
  identifier << '-';
  identifier << gen();
  return identifier.str();
}
