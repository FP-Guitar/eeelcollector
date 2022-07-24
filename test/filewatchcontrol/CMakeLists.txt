set(TEST_NAME Filewatchcontrol)
add_executable(${TEST_NAME}
	WatchTriggerDirectoryTask_Test.cpp
	)
target_link_libraries(${TEST_NAME} PRIVATE appcontrol testutil GTest::gtest_main eeelcollector::project_options eeelcollector::project_warnings)
gtest_discover_tests(${TEST_NAME})
