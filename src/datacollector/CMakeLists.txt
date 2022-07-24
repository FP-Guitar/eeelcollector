set(TARGET_NAME datacollector)

add_library(${TARGET_NAME}
	util.cpp
	include/datacollector/util.h
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PUBLIC project_options project_warnings)