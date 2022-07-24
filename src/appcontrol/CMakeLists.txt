set(TARGET_NAME appcontrol)

add_library(${TARGET_NAME}
	Configuration.cpp
	WatchTriggerDirectoryTask.cpp
	include/appcontrol/WatchTriggerDirectoryTask.h
	include/appcontrol/Configuration.hpp
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PUBLIC dirwatcher project_options project_warnings PRIVATE fmt::fmt spdlog::spdlog)
