set( TARGET_NAME dirwatcher)

add_library(${TARGET_NAME}  FilenameMatcher.cpp include/dirwatcher/FilenameMatcher.h)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${TARGET_NAME} PRIVATE project_options project_warnings)