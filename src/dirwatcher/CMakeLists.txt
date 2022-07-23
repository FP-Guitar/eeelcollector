set(TARGET_NAME dirwatcher)

add_library(${TARGET_NAME}
	FileFilter.cpp
	DirectoryFileListRetriever.cpp
	FilenameMatcher.cpp
	TriggerFileCache.cpp
	include/dirwatcher/FilenameMatcher.h
	include/dirwatcher/DirectoryFileListRetriever.h
	include/dirwatcher/FileFilter.h
	include/dirwatcher/TriggerFileCache.h
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PUBLIC project_options project_warnings)