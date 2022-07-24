
#include "include/datacollector/TarFileStorage.hpp"
#include <cstdlib>
#include <datacollector/util.h>

#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>
#include <utility>
void eeelcollector::datacollector::TarFileStorage::StoreObject(const eeelcollector::datacollector::CollectionInfoObject &object) const {
  // THIS IS VERY VERY HACKY
  std::stringstream tarDiredtory;
  tarDiredtory << "tar ";
  tarDiredtory << "-cf ";
  tarDiredtory << " " << targetDirectory_.c_str() << "/";
  auto filename = util::CreateUniqueIdentifierFromPath(object.collectionTarget);
  tarDiredtory << filename;
  tarDiredtory << ".tar ";
  tarDiredtory << object.collectionTarget;
  auto tarDirectoryAsString = tarDiredtory.str();
  spdlog::info("Executiong {}", tarDirectoryAsString);
// NOLINTNEXTLINE(cert-env33-c)
  if (std::system(tarDirectoryAsString.c_str()) != 0) {
	spdlog::error("Executiong {}", tarDirectoryAsString);
  } else {
	auto tmpFile = std::filesystem::temp_directory_path()/="collection.json";
	auto json = util::ConvertToJson(object);
	auto file = std::ofstream(tmpFile);
	file << json;
	file.close();
	std::stringstream addCollection;
	addCollection << "tar ";
	addCollection << " -uf ";
	addCollection << " " << targetDirectory_.c_str() << "/";
	addCollection << filename;
	addCollection << ".tar ";
	addCollection << "-C ";
	addCollection << std::filesystem::temp_directory_path();
	addCollection << " " << tmpFile.filename().c_str();

	auto addCOllectionASString = addCollection.str();
	spdlog::info("Executiong {}", addCOllectionASString);
// NOLINTNEXTLINE(cert-env33-c)
	if (std::system(addCOllectionASString.c_str()) != 0) {
	  spdlog::error("Executiong {}", addCOllectionASString);
	}

  }


}
eeelcollector::datacollector::TarFileStorage::TarFileStorage(std::filesystem::path targetDirectory) : targetDirectory_{std::move(
	targetDirectory)} {
  spdlog::warn(
	  "Experimental tar storing... make sure you have tar in path... ask your friendly programmer to replace this soon");
}
