set(TARGET_NAME testutil)

add_library(${TARGET_NAME}
	testutil.h
	testutil.cpp
	)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET_NAME} PUBLIC project_options project_warnings)
target_compile_definitions(${TARGET_NAME} PUBLIC RESOURCES="${CMAKE_SOURCE_DIR}/test/_resources")

set(TEST_NAME testutil_Test)
add_executable(${TEST_NAME}
	testutil_Test.cpp
	)
target_link_libraries(${TEST_NAME} PRIVATE testutil GTest::gtest_main eeelcollector::project_options eeelcollector::project_warnings)
gtest_discover_tests(${TEST_NAME})