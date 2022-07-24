set(TEST_NAME TestDatacollector)
add_executable(${TEST_NAME}
	util_Test.cpp
	CollectDiskUsageTest.cpp
	CollectFIlesTest.cpp
	)
target_link_libraries(${TEST_NAME} PRIVATE
	datacollector
	testutil nlohmann_json::nlohmann_json GTest::gtest_main eeelcollector::project_options eeelcollector::project_warnings)
gtest_discover_tests(${TEST_NAME})
