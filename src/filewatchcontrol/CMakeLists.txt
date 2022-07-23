set(TARGET_NAME filewatchcontrol)

add_library(${TARGET_NAME} WatchTriggerDirectoryTask.cpp include/filewatchcontrol/WatchTriggerDirectoryTask.h
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PUBLIC dirwatcher project_options project_warnings PRIVATE fmt::fmt spdlog::spdlog)
