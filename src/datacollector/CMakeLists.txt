set(TARGET_NAME datacollector)

add_library(${TARGET_NAME}
	util.cpp
	CollectDiskUsageWithSTL.cpp
	CollectFilesAtTarget.cpp
	TarFileStorage.cpp
	include/datacollector/DataCollector.hpp
	include/datacollector/CollectFilesAtTarget.hpp
	include/datacollector/CollectionInfoObject.hpp
	include/datacollector/CollectAvailableSpaceWithSTL.hpp
	include/datacollector/util.h
	include/datacollector/TarFileStorage.hpp
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PUBLIC project_options project_warnings PRIVATE spdlog::spdlog nlohmann_json::nlohmann_json stduuid::stduuid)