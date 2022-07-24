set(TARGET_NAME appcontrol)

add_library(${TARGET_NAME}
	Configuration.cpp
	WatchTriggerDirectoryTask.cpp
	CollectFilesTask.cpp
	include/appcontrol/WatchTriggerDirectoryTask.h
	include/appcontrol/Configuration.hpp
	include/appcontrol/CollectFilesTask.hpp
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
target_link_libraries(${TARGET_NAME} PUBLIC dirwatcher  datacollector  project_options project_warnings PRIVATE CLI11::CLI11 fmt::fmt spdlog::spdlog )
